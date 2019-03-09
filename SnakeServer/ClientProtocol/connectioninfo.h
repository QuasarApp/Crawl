#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include <QString>

class ConnectionInfo
{
private:
    QString addres = "";
public:
    ConnectionInfo(const QString & addrrss);
    bool operator == (const ConnectionInfo &otherInfo) const;

    QString getAddres() const;
};

#endif // CONNECTIONINFO_H
