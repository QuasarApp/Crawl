#include "notificationservice.h"

NotificationService::NotificationService(QObject * ptr): QObject (ptr) {

}

QString NotificationService::notify() const {
    return _notify;
}

void NotificationService::setNotify(const QString& notify) {
    if (_notify == notify)
        return;

    _notify = notify;
    _history.push_back(_notify);

    emit notifyChanged(_notify);
}

NotificationService *NotificationService::getService() {
    static auto service = new NotificationService;
    return service;
}

const QStringList &NotificationService::history() const {
    return _history;
}
