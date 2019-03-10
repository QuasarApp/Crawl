#include <QCoreApplication>
#include <serverutils.h>
#include <quasarapp.h>
#include <serverutils.h>
#include <mainserver.h>

int main(int argc, char *argv[])
{
    if (!ServerUtils::parseParams(argc, argv)) {
        ServerUtils::help();
        return 1;
    }

    if (QuasarAppUtils::Params::isEndable("help") ||
            QuasarAppUtils::Params::isEndable("h")) {
        ServerUtils::help();
        return 0;
    }

    if(ServerUtils::runDaemon()) {
        return 0;
    }

    QCoreApplication a(argc, argv);

    MainServer loclaServer;

    return a.exec();
}
