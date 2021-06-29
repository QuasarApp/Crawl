//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "clasteritem.h"
#include "snake.h"
#include "snakeitem.h"
#include <QQuaternion>
#include <quasarapp.h>
#include <cmath>

Snake::Snake(const QString &name, const QString &viewTempalte, QObject *ptr):
    IPlayer (name, viewTempalte, ptr) {

    _vectors = new QVector3D[2];
    setAngularVelocity(100);
    setSpeed(100);

    setLengthBetwinItems(1);
    setBodyCount(50);
    setSpeed(100);

    _clickIndex = 0;

    setScales({{0, 0.8},
              {0.4, 1.2},
              {1, 0.5}});
}

Snake::~Snake( ){
    delete [] _vectors;
}

void Snake::render(unsigned int tbfMsec) {
    IPlayer::render(tbfMsec);
}

void Snake::add(ClasterItem *object) {
    if (auto snakeItem = dynamic_cast<SnakeItem*>(object)) {

        if (_lastSnakeItem) {
            snakeItem->setPrev(_lastSnakeItem);
        } else {
            snakeItem->setPrev(this);
        }

        snakeItem->setBreakingForce(breakingForce());

        _lastSnakeItem = static_cast<IWorldItem*>(snakeItem);

        Claster::add(object);
        return ;
    }

    QuasarAppUtils::Params::log("Failed to add item to Snake."
                                " You need to use the SnakeItem child class as a argument",
                                QuasarAppUtils::Error);
}

void Snake::remove(ClasterItem *object) {

    if (_lastSnakeItem == object) {
        _lastSnakeItem = static_cast<const SnakeItem*>(_lastSnakeItem)->prev();
    }

    return Claster::remove(object);
}

void Snake::remove(int id) {
    if (_lastSnakeItem->guiId() == id) {
        _lastSnakeItem = static_cast<const SnakeItem*>(_lastSnakeItem)->prev();
    }

    return Claster::remove(id);
}

void Snake::init() {
    generateBody();
}

void Snake::onTap() {
    setMovableVector(_vectors[_clickIndex++ % 2]);
}

void Snake::generateBody() {

    auto scaleIt = _scales.begin();

    float from = 0, fromKey = 0;
    float to = scaleIt.value(), toKey = scaleIt.key();

    for(int i = 0; i < _bodyCount; ++i) {
        if (!_factory) {
            QuasarAppUtils::Params::log("Please use the registerBodyitem method"
                                        " before invoke parent constructor.",
                                        QuasarAppUtils::Error);
            return;
        }

        auto item = _factory();

        float scale = 1;
        if (scaleIt != _scales.end()) {
            float position = static_cast<float>(i) / _bodyCount;
            while (position >= scaleIt.key() && scaleIt != _scales.end()) {
                scaleIt++;

                if (scaleIt != _scales.end()) {
                    from = to;
                    to = scaleIt.value();
                    fromKey = toKey;
                    toKey = scaleIt.key();
                }
            }

            scale = ((position - fromKey) * toKey / (to - from)) + from;
        }

        item->setSize(item->size() * scale);

        add(item);
    }
}

float Snake::speed() const {
    return _speed;
}

void Snake::setSpeed(float newSpeed) {
    _speed = newSpeed;
    float asixPos = std::sqrt(std::pow(_speed, 2.0) / 2);
    _vectors[0] = QVector3D(asixPos, asixPos,0); // left tap
    _vectors[1] = QVector3D(asixPos,-asixPos,0); // right tap
}

int Snake::bodyCount() const {
    return _bodyCount;
}

void Snake::setBodyCount(int newBodyCount) {
    _bodyCount = newBodyCount;
}

const QMap<float, float> &Snake::scales() const {
    return _scales;
}

void Snake::setScales(const QMap<float, float> &newScales) {
    _scales = newScales;
}

float Snake::lengthBetwinItems() const{
    return _lengthBetwinItems;
}

void Snake::setLengthBetwinItems(float newLengthBetwinItems) {
    _lengthBetwinItems = newLengthBetwinItems;
}
