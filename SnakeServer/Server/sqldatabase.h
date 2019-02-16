#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <QObject>

class SQLDataBase : public QObject
{
    Q_OBJECT
public:
    SQLDataBase(QObject * ptr = nullptr);
};

#endif // SQLDATABASE_H
