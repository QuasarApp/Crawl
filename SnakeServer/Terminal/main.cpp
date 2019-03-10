#include <QCoreApplication>
#include <quasarapp.h>
#include <client.h>
#include <QDebug>
#include <serverutils.h>

void handleResponcke(const QVariantMap &data) {
    for(auto iter = data.begin(); iter != data.end(); ++iter) {
        qInfo() << QString("%0: %1").arg( iter.key()).arg(iter.value().toString());
    }

    QCoreApplication::exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QuasarAppUtils::Params::parseParams(argc, argv);

    ServerProtocol::Client cli;

    QObject::connect(&cli, &ServerProtocol::Client::sigIncommingData,
                     &handleResponcke);

    if (QuasarAppUtils::Params::isEndable("ping")) {
        ServerProtocol::Package pkg;
        pkg.hdr.command = ServerProtocol::Ping;
        if (!cli.sendPackage(pkg)) {
            qCritical() << "command not sendet!";
            return 1;
        }
    } else if (QuasarAppUtils::Params::isEndable("Help") ||
               QuasarAppUtils::Params::isEndable("h")) {

        ServerUtils::helpClient();

    } else if (QuasarAppUtils::Params::isEndable("State")) {

        cli.getState();

    } else if (QuasarAppUtils::Params::isEndable("Ban")) {

        auto address = QuasarAppUtils::Params::getStrArg("Ban");
        cli.ban(QHostAddress(address));

    } else if (QuasarAppUtils::Params::isEndable("Unban")) {

        auto address = QuasarAppUtils::Params::getStrArg("Ban");
        cli.unBan(QHostAddress(address));

    } else if (QuasarAppUtils::Params::isEndable("Restart")) {

        QStringList address = QuasarAppUtils::Params::getStrArg("Restart").split(":");
        cli.restart(address[0], static_cast<quint16>(address[1].toShort()));
    }
    else {
        ServerUtils::helpClient();
        return 0;
    }

    return a.exec();
}
