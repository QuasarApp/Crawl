#include <QCoreApplication>
#include <serverutils.h>
#include <quasarapp.h>

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

    if (ServerUtils::runDaemon()) {
        
    }

    QCoreApplication a(argc, argv);

    return a.exec();
}
