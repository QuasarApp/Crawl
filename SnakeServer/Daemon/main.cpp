#include <QCoreApplication>
#include <serverutils.h>
#include <quasarapp.h>
#include <serverutils.h>
#include <mainserver.h>

int main(int argc, char *argv[])
{
    if (!ServerUtils::parseParams(argc, argv)) {
        ServerUtils::helpDaemon();
        return 1;
    }

    if (QuasarAppUtils::Params::isEndable("help") ||
            QuasarAppUtils::Params::isEndable("h")) {
        ServerUtils::helpDaemon();
        return 0;
    }

    QString address = "";
    unsigned short port = 0;

    if(QuasarAppUtils::Params::isEndable("address")) {
        address = QuasarAppUtils::Params::getStrArg("address");
    }

    if(QuasarAppUtils::Params::isEndable("port")) {
        port = QuasarAppUtils::Params::getStrArg("port").toUShort();
    }

    QCoreApplication a(argc, argv);

    MainServer mainServer;
    if (!mainServer.run(address, port)) {
        QuasarAppUtils::Params::verboseLog("server is not run!");
        ServerUtils::helpDaemon();
        return 1;
    }

    if(ServerUtils::runDaemon()) {
        return 0;
    }

    return a.exec();
}
