#include "player.h"

QString Player::name() const {
    return _name;
}

void Player::setName(const QString &name) {
    _name = name;
}

QString Player::post() const {
    return _post;
}

void Player::setPost(const QString &post) {
    _post = post;
}

unsigned int Player::maney() const {
    return _maney;
}

void Player::setManey(unsigned int maney) {
    _maney = maney;
}

unsigned int Player::record() const {
    return _record;
}

void Player::setRecord(unsigned int record) {
    _record = record;
}

QList<int> Player::items() const {
    return _items;
}

void Player::setItems(const QList<int> &items) {
    _items = items;
}

unsigned int Player::currentSnake() const {
    return _currentSnake;
}

void Player::setCurrentSnake(unsigned int currentSnake) {
    _currentSnake = currentSnake;
}

bool Player::isValid() const {
    return !(_name.isEmpty() || _items.isEmpty() || _post.isEmpty());
}

QDataStream &operator >>(QDataStream &stream, Player &data) {

    stream >> data._name;
    stream >> data._post;
    stream >> data._maney;
    stream >> data._record;
    stream >> data._items;
    stream >> data._currentSnake;

    return stream;
}

QDataStream &operator <<(QDataStream &stream, const Player &data) {
    stream << data._name;
    stream << data._post;
    stream << data._maney;
    stream << data._record;
    stream << data._items;
    stream << data._currentSnake;

    return stream;
}

Player::Player() {
}

