#include <QCoreApplication>
#include <quasarapp.h>
#include <client.h>
#include <QDebug>
#include <serverutils.h>
#include <QTimer>

void handleResponcke(const QVariantMap &data) {
    for(auto iter = data.begin(); iter != data.end(); ++iter) {
        qInfo() << QString("%0: %1").arg( iter.key()).arg(iter.value().toString());
    }

    QCoreApplication::exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QuasarAppUtils::Params::parseParams(argc, const_cast<const char**>(argv));

    ServerProtocol::Client cli;

    QObject::connect(&cli, &ServerProtocol::Client::sigIncommingData,
                     &handleResponcke);

    if (QuasarAppUtils::Params::isEndable("ping")) {

        if (!cli.ping()) {
            qCritical() << "command not sendet!";
            return 1;
        }

    } else if (QuasarAppUtils::Params::isEndable("Help") ||
               QuasarAppUtils::Params::isEndable("h")) {

        ServerUtils::helpClient();
        return 0;

    } else if (QuasarAppUtils::Params::isEndable("State")) {

        if (!cli.getState()) {
            qCritical() << "command not sendet!";
            return 1;
        };

    } else if (QuasarAppUtils::Params::isEndable("Ban")) {

        auto address = QuasarAppUtils::Params::getStrArg("Ban");

        if (!cli.ban(QHostAddress(address))) {
            qCritical() << "command not sendet!";
            return 1;
        }

    } else if (QuasarAppUtils::Params::isEndable("Unban")) {

        auto address = QuasarAppUtils::Params::getStrArg("Ban");
        if (!cli.unBan(QHostAddress(address))) {
            qCritical() << "command not sendet!";
            return 1;
        }

    } else if (QuasarAppUtils::Params::isEndable("Restart")) {

        QStringList address = QuasarAppUtils::Params::getStrArg("Restart").split(":");
        if (!cli.restart(address[0], static_cast<quint16>(address[1].toShort()))) {
            qCritical() << "command not sendet!";
            return 1;
        }
    }
    else {
        ServerUtils::helpClient();
        return 0;
    }

    QTimer::singleShot(3000, [&a] {
        qCritical() << "server not responsed !";
        a.exit(1);
    });

    return a.exec();
}
