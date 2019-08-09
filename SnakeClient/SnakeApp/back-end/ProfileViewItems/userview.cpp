#include "userview.h"

const PlayerClientData *UserView::getSource() const {
    return _source.data();
}

void UserView::setSource(QSharedPointer<PlayerClientData> data) {

    _offline = data == nullptr;

    if (data->id() != _source->id()) {
        _source = data;
        emit sourceChanged();
    }
}

bool UserView::offline() const {
    return _offline;
}

void UserView::setOffline(bool offline) {
    if (_offline != offline) {
        emit offlineChanged(_offline = offline);
    }
}

UserView::UserView(QObject *parent) : QObject(parent) {

}

QString UserView::name() const {
    if (!_source) {
        return tr("Undefined name");
    }
    return _source->getName();
}

QString UserView::gmail() const {
    if (!_source) {
        return tr("Undefined gmail");
    }
    return _source->getGmail();
}

int UserView::money() const {
    if (!_source) {
        return -1;
    }
    return static_cast<int>(_source->getMany());
}

int UserView::record() const {
    if (!_source) {
        return -1;
    }
    return static_cast<int>(_source->getRecord());
}

int UserView::avgRecord() const {
    if (!_source) {
        return -1;
    }
    return static_cast<int>(_source->getAvgRecord());
}

int UserView::cureentSnake() const {
    if (!_source) {
        return -1;
    }
    return _source->getCureentSnake();
}

int UserView::id() const {
    if (!_source) {
        return -1;
    }
    return _source->id();
}
