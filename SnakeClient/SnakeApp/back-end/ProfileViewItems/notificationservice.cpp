#include "notificationservice.h"

NotificationService::NotificationService(QObject * ptr): QObject (ptr) {
    qRegisterMetaType<NotificationData>("NotificationData");
    qRegisterMetaType<QList<NotificationData>> ("QList<NotificationData>");

}

NotificationData NotificationService::notify() const {
    return _notify;
}

void NotificationService::setNotify(const NotificationData& notify) {
    if (_notify == notify)
        return;

    _notify = notify;
    _history.push_back(_notify);

    emit notifyChanged();
}

NotificationService *NotificationService::getService() {
    static auto service = new NotificationService;
    return service;
}

const QList<NotificationData> &NotificationService::history() const {
    return _history;
}
