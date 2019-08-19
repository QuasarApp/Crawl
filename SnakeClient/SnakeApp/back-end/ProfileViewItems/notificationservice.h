#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include "notificationdata.h"

#include <QObject>

class NotificationService: public QObject
{
    Q_OBJECT

    Q_PROPERTY(NotificationData notify READ notify NOTIFY notifyChanged)
    Q_PROPERTY(QList<NotificationData> history READ history NOTIFY notifyChanged)

private:
    explicit NotificationService(QObject *ptr = nullptr);

    NotificationData _notify;
    QList<NotificationData> _history;

public:
    NotificationData notify() const;
    void setNotify(const NotificationData &notify);
    static NotificationService* getService();

    const QList<NotificationData> & history() const;

signals:
    void notifyChanged();
};



#endif // NOTIFICATIONSERVICE_H
