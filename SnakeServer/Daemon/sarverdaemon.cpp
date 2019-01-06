#include "sarverdaemon.h"
#include <exception>

SarverDaemon::SarverDaemon() {

    if (!localServer.listen(DEFAULT_SERVER)) {
        throw std::runtime_error("local server not started! " +
                                 localServer.errorString().toStdString());
    }

}
