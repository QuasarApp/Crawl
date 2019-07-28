#include "userview.h"

const PlayerClientData *UserView::getSource() const {
    return _source;
}

void UserView::setSource(const PlayerClientData *value) {
    if (value->id() != _source->id()) {
        _source = value;
        emit sourceChanged();
    }
}

UserView::UserView(QObject *parent) : QObject(parent) {

}

QString UserView::name() const {
    return _source->getName();
}

QString UserView::gmail() const {
    return _source->getGmail();
}

int UserView::money() const {
    return static_cast<int>(_source->getMany());
}

int UserView::record() const {
    return static_cast<int>(_source->getRecord());
}

int UserView::avgRecord() const {
    return static_cast<int>(_source->getAvgRecord());
}

int UserView::cureentSnake() const {
    return _source->getCureentSnake();
}

int UserView::id() const {
    return _source->id();
}
