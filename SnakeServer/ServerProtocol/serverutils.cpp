#include "serverutils.h"
#include <QtDebug>
#include <quasarapp.h>
#include <unistd.h>

ServerUtils::ServerUtils() {

}

void ServerUtils::help() {
    qInfo() << "";
    qInfo() << "Usage: SnakeServer <[params]> ";
    qInfo() << "";
    qInfo() << "Options:";
    qInfo() << "   help / h                 : show help.";
    qInfo() << "   daemon / d                 : show help.";

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
