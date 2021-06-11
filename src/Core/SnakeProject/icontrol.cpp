#include "icontrol.h"

IControl::IControl() {

}

const QString &IControl::view() const {
    return _view;
}

bool IControl::init() {
    setView(initQmlView());
    return _view.size();
}

void IControl::setView(const QString &newView) {
    if (_view == newView)
        return;
    _view = newView;
    emit viewChanged();
}
