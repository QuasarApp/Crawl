#ifndef SETTINGSVIEWMODEL_H
#define SETTINGSVIEWMODEL_H

#include <QObject>
#include "./../settings.h"


class SettingsViewModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)

private:
    Settings *_cfg = nullptr;

private slots:
    void handleValueChanged(QString key, QVariant value);

public:
    SettingsViewModel(QObject* ptr = nullptr);
    int port() const;
    QString host() const;
    int theme() const;

    Q_INVOKABLE void forceUpdate();
    Q_INVOKABLE void toDefault();


public slots:
    void setPort(int port);
    void setHost(const QString &host);
    void setTheme(int theme);

signals:
    void portChanged(int port);
    void hostChanged(const QString &host);
    void themeChanged(int theme);
};

#endif // SETTINGSVIEWMODEL_H
