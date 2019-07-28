#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include <QObject>

class UserView;

class NetworkProfileMainModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userViewModel READ userViewModel NOTIFY userViewModelChanged)

    UserView* _userViewModel = nullptr;

public:
    NetworkProfileMainModel(QObject *ptr = nullptr);

    QObject* userViewModel() const;
signals:
    void userViewModelChanged(QObject* userViewModel);
};

#endif // NETWORKPROFILEMAINMODEL_H
