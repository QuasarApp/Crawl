#include "serverutils.h"
#include <QtDebug>
#include <quasarapp.h>
#include <unistd.h>

ServerUtils::ServerUtils() {

}

void ServerUtils::helpDaemon() {

    qInfo() << "";
    qInfo() << "Usage: SnakeServer-daemon.sh <[params]> ";
    qInfo() << "";
    qInfo() << "Options:";
    qInfo() << "   help / h                 : show help.";
    qInfo() << "   daemon / d               : show help.";

    qInfo() << "   verbose                  : show debug log";

    qInfo() << "";
}

void ServerUtils::helpClient() {

    qInfo() << "";
    qInfo() << "Usage: Terminal.sh <[params]> ";
    qInfo() << "";
    qInfo() << "Options:";
    qInfo() << "   help / h                 : show help.";
    qInfo() << "   Ping                     : debug commnad";
    qInfo() << "   State                    : show information about deamon";
    qInfo() << "   -Ban (address)           : ban user with address";
    qInfo() << "   -Unban (address)         : unban user with address";
    qInfo() << "   -Restart (address:port)  : restarrt server deamon with new address and port";

    qInfo() << "   verbose                  : show debug log";

    qInfo() << "";
}

bool ServerUtils::runDaemon() {
    if (QuasarAppUtils::Params::isEndable("daemon") ||
            QuasarAppUtils::Params::isEndable("d")) {

        int pid = fork();
        if (pid != 0) {
            return true;
        }
    }

    return false;
}

bool ServerUtils::parseParams(int argc, char *argv[]) {
    if ( !QuasarAppUtils::Params::parseParams(argc, argv)) {
        return false;
    }

    return true;
}
