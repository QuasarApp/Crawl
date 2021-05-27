#ifndef SETTINGSVIEWMODEL_H
#define SETTINGSVIEWMODEL_H

#include <QObject>
#include "SnakeProject/settings.h"


class SettingsViewModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)

private:
    Settings *_cfg = nullptr;

private slots:
    void handleValueChanged(QString key, QVariant value);

public:
    SettingsViewModel(QObject* ptr = nullptr);
    int theme() const;

    Q_INVOKABLE void forceUpdate();
    Q_INVOKABLE void toDefault();


public slots:
    void setTheme(int theme);

signals:
    void themeChanged(int theme);
};

#endif // SETTINGSVIEWMODEL_H
