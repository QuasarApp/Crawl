#include "networkprofilemainmodel.h"
#include "userview.h"

NetworkProfileMainModel::NetworkProfileMainModel(QObject *ptr): QObject (ptr) {
    _userViewModel = new UserView (this);
}

QObject *NetworkProfileMainModel::userViewModel() const {
    return _userViewModel;
}
