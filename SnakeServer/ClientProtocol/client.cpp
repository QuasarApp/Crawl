#include "client.h"
#include <QRegularExpression>
#include <QTcpSocket>
#include <QVariantMap>
#include <QDateTime>
#include <quasarapp.h>
#include <qrsaencryption.h>
#include <pubkey.h>
#include "factorynetobjects.h"
#include "gamedata.h"
#include "getitem.h"
#include "login.h"
#include "updateplayerdata.h"

namespace ClientProtocol {

// TODO
Command Client::checkCommand(int sig, Command reqCmd, Type type) {

#define idx static_cast<quint8>(sig)

    auto expCmd = static_cast<Command>(
                _requestsMap[idx].value("expected",
                                        static_cast<quint8>(Command::Undefined)).toInt());

    if (expCmd == Command::Undefined ||
            expCmd != reqCmd ||
            type != Type::Responke) {

        return Command::Undefined;
    }

    _requestsMap[idx]["time"] = QDateTime::currentMSecsSinceEpoch();
    return expCmd;
}

void Client::updateStatuses(Command extCmd, Command cmd, Type type, const QByteArray& obj)
{
    setOnlineStatus(extCmd != Command::Undefined && type == Type::Responke);

    if (extCmd == Command::Login
             && type == Type::Responke) {

        UpdatePlayerData data;
        data.fromBytes(obj);
        bool validData = data.isValid();
        if (validData) {
            _token = data.getToken();

        }

        setLoginStatus(cmd == Command::UpdatePlayerData && validData);
    }
}

bool Client::receiveData(const QByteArray &obj, Header hdr) {

    auto command = static_cast<Command>(hdr.command);
    auto requesCommand = static_cast<Command>(hdr.requestCommand);

    auto type = static_cast<Type>(hdr.type);

    if (command == Command::PubKey && !_rsaKey.size()) {
        PubKey data;       
        data.fromBytes(obj);
        return setRSAKey(data.getKey());;
    }

    auto expectedCommand = checkCommand(hdr.sig, requesCommand, type);

    if (expectedCommand == Command::Undefined) {
        QuasarAppUtils::Params::verboseLog("wrong sig of package");
        return false;
    }

    updateStatuses(expectedCommand, command, type, obj);

    emit sigIncommingData(static_cast<Command>(hdr.command), obj);

    return true;
}

bool Client::setRSAKey(const QByteArray& key) {
    bool newStatus = QRSAEncryption::isValidRsaKey(key);
    setOnlineStatus(newStatus);

    if (newStatus) {
        _rsaKey = key;
    }

    return newStatus;
}

void Client::setLoginStatus(bool newStatus) {
    if (newStatus != _logined) {
        _logined = newStatus;
        emit loginChanged(_logined);
    }
}

void Client::setOnlineStatus(bool newOnline) {
    if (newOnline != _online) {
        _online = newOnline;
        emit onlineChanged(_online);
        if (!_online) {
            _rsaKey = "";
            setLoginStatus(false);
        }
    }
}

void Client::incommingData() {
    auto array = _destination->readAll();

    if (_downloadPackage.hdr.isValid()) {
        _downloadPackage.data.append(array);

    } else {
        memcpy(&_downloadPackage.hdr,
               array.data(), sizeof(Header));
        _downloadPackage.data.append(array.mid(sizeof(Header)));
    }

    if (_downloadPackage.isValid()) {
        if (!receiveData(_downloadPackage.data, _downloadPackage.hdr)) {
            // ban
        }

        _downloadPackage.reset();
        return;
    }
}

void Client::handleDisconnected() {
    setOnlineStatus(false);
}

Client::Client(const QString &addrress, unsigned short port, QObject *ptr):
    QObject (ptr) {

    _destination = new QTcpSocket(this);

    _destination->connectToHost(addrress, port);

    connect(_destination, &QTcpSocket::readyRead,
            this, &Client::incommingData);

    connect(_destination, &QTcpSocket::disconnected,
            this, &Client::handleDisconnected);
}

bool Client::sendPackage(Package &pkg) {
    if (!pkg.isValid()) {
        return false;
    }

    if (!_destination->isValid()) {
        qCritical() << "destination server not valid!";
        return false;
    }

    if (!_destination->waitForConnected()) {
        qCritical() << "no connected to server! " << _destination->errorString();
        return false;
    }

    auto index = nextIndex();
    _requestsMap[index] = {{"expected", static_cast<const unsigned short>(pkg.hdr.command)}};
    pkg.hdr.sig = index;

    QByteArray bytes = pkg.toBytes();
    bool sendet = bytes.size() == _destination->write(bytes);

    return sendet;
}

unsigned char Client::nextIndex() {
    return static_cast<unsigned char>((currentIndex++) % 256);
}

bool Client::ping() {

    Package pcg;

    if (!pcg.create(Command::Ping, Type::Request)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
}

bool Client::login(const QString &gmail, const QByteArray &pass) {
    if (!pass.size()) {
        return false;
    }

    if (!gmail.size()) {
        return false;
    }

    if (!isOnline()) {
        return false;
    }

    Package pcg;

    Login login;

    login.setHashPass(QRSAEncryption::encodeS(
                          QCryptographicHash::hash(pass, QCryptographicHash::Sha256),
                          _rsaKey));
    login.setGmail(gmail);
    login.setId(0);

    if (!login.isValid()) {
        return false;
    }

    if (!pcg.create(&login, Type::Request)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
}

void Client::loginOut() {
    _token = "";
    setLoginStatus(false);
}

bool Client::updateData() {

    if (!isLogin()) {
        return false;
    }

    Package pcg;

    UpdatePlayerData rec;
    rec.setToken(_token);
    rec.setId(0);

    if (!rec.isValid()) {
        return false;
    }

    if (!pcg.create(&rec, Type::Request)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;
    }

    return true;
}

bool Client::savaData(const QList<int>& gameData) {
    if (!isLogin()) {
        return false;
    }

    Package pcg;

    GameData rec;
    rec.setToken(_token);
    rec.setTimeClick(gameData);
    rec.setId(0);

    if (!rec.isValid()) {
        return false;
    }

    if (!pcg.create(&rec, Type::Request)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;
    }

    return true;
}

bool Client::getItem(int id) {

    if (!isLogin()) {
        return false;
    }

    if (!id) {
        return false;
    }

    Package pcg;

    GetItem rec;
    rec.setToken(_token);
    rec.setId(id);

    if (!rec.isValid()) {
        return false;
    }

    if (!pcg.create(&rec, Type::Request)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;
    }

    return true;
}

const bool& Client::isOnline() const {
    return _online;
}

const bool& Client::isLogin() const {
    return _logined;
}

}
