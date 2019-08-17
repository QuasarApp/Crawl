#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <QObject>

class NotificationService: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString notify READ notify NOTIFY notifyChanged)
    Q_PROPERTY(QStringList history READ history NOTIFY notifyChanged)

private:
    explicit NotificationService(QObject *ptr = nullptr);

    QString _notify;
    QStringList _history;

public:
    QString notify() const;
    void setNotify(const QString &notify);
    static NotificationService* getService();

    const QStringList& history() const;

signals:
    void notifyChanged(QString notify);
};



#endif // NOTIFICATIONSERVICE_H
