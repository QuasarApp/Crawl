#include "connectioninfo.h"

QString ConnectionInfo::getAddres() const
{
    return addres;
}

ConnectionInfo::ConnectionInfo(const QString &addrrss) {
    addres = addrrss;
}

bool ConnectionInfo::operator ==(const ConnectionInfo &otherInfo) const {
    return addres == otherInfo.addres;
}
