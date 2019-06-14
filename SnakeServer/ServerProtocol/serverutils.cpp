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
    qInfo() << "   daemon / d               : start like daemon.";
    qInfo() << "   -port (port)             : start with custom port.";
    qInfo() << "   -address (address)       : start with custom address.";
    qInfo() << "   -db (path/to/db.file)    : start with custom db";

    qInfo() << "   verbose                  : show debug log";

    qInfo() << "";
}

void ServerUtils::helpClient() {

    qInfo() << "";
    qInfo() << "Usage: Terminal.sh <[params]> ";
    qInfo() << "";
    qInfo() << "Options:";
    qInfo() << "   help / h                 : show help.";
    qInfo() << "   ping                     : debug commnad";
    qInfo() << "   state                    : show information about deamon";
    qInfo() << "   stop                     : stop server deamon";
    qInfo() << "   -ban (address)           : ban user with address";
    qInfo() << "   -unban (address)         : unban user with address";
    qInfo() << "   -restart (address:port)  : restarrt server deamon with new address and port";
    qInfo() << "   -start (address:port)    : start server deamon with custom address";
    qInfo() << "   start                    : start server deamon with default address";

    qInfo() << "   verbose                  : show debug log";

    qInfo() << "";
}

bool ServerUtils::runDaemon() {

#ifdef Q_OS_UNIX
    if (QuasarAppUtils::Params::isEndable("daemon") ||
            QuasarAppUtils::Params::isEndable("d")) {

        int pid = fork();
        if (pid != 0) {
            return true;
        }
    }

#endif
    return false;
}

bool ServerUtils::parseParams(int argc, char *argv[]) {
    if ( !QuasarAppUtils::Params::parseParams(argc, const_cast<const char**>(argv))) {
        return false;
    }

    return true;
}
