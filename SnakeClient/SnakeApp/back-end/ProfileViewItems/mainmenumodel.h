#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include <QObject>

class UserView;

class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userViewModel READ userViewModel NOTIFY userViewModelChanged)
    Q_PROPERTY(bool online READ online NOTIFY onlinelChanged)
    Q_PROPERTY(bool login READ login NOTIFY loginChanged)

    UserView* _userViewModel = nullptr;

public:
    MainMenuModel(QObject *ptr = nullptr);

    QObject* userViewModel() const;
    bool online() const;

    bool login() const;

signals:
    void userViewModelChanged(QObject* userViewModel);
    void newGame();

    void onlinelChanged(bool online);
    void loginChanged(bool login);
};

#endif // NETWORKPROFILEMAINMODEL_H
