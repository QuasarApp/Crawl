#ifndef NOTIFICATIONDATA_H
#define NOTIFICATIONDATA_H
#include <QObject>

class NotificationData
{
    Q_GADGET
    Q_PROPERTY(QString text READ text)
    Q_PROPERTY(QString img READ img)
    Q_PROPERTY(QString title READ title)

    QString _text;
    QString _img;
    QString _title;

public:
    explicit NotificationData(const QString& title = "", const QString& text = "", const QString& img = "");
    Q_INVOKABLE QString text() const;
    Q_INVOKABLE QString img() const;
    Q_INVOKABLE QString title() const;
    bool operator ==(const NotificationData &righ);
};

#endif // NOTIFICATIONDATA_H
