//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "snake.h"
#include "snakeitem.h"
#include <QQuaternion>
#include <quasarapp.h>
#include <cmath>
#include "iworld.h"

namespace CRAWL {


Snake::Snake(const QString &name, const QString &viewTempalte, QObject *ptr):
    PlayableObject (name, viewTempalte, ptr) {

    _vectors = new QVector3D[2];
    setAngularVelocity(100);

    setLengthBetwinItems(1);
    setSpeed(100);

    _clickIndex = 0;

    setScales({{0, 0.8},
              {0.4, 1.2},
              {1, 0.5}});

    setLengthBetwinItemsMap({{0, 0.8},
                              {0.4, 1.2},
                              {1, 0.5}});

    addSupportOfEvent(Events::Intersects);
}

Snake::~Snake( ){
    delete [] _vectors;
}

QString Snake::itemTextType() const {
    return Snake::typeText();
}

QString Snake::typeText() {
    return "PlayableObject";
}

unsigned int Snake::type() {
    return qHash(typeText());
}

void Snake::render(unsigned int tbfMsec) {
    PlayableObject::render(tbfMsec);
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
    generateItems();
}

void Snake::onTap() {
    setMovableVector(_vectors[_clickIndex++ % 2]);
}

float CRAWL::Snake::getValueFromMap(const QMap<float, float> &map,
                                    float position,
                                    float defaultValue) {
    auto it = map.cbegin();

    float from = 0, fromKey = 0;
    float to = it.value(), toKey = it.key();

    if (it != _scales.cend()) {
        while (position >= it.key() && it != _scales.cend()) {
            it++;

            if (it != _scales.cend()) {
                from = to;
                to = it.value();
                fromKey = toKey;
                toKey = it.key();
            }
        }

        float localPosition = (position - fromKey) / (fromKey - toKey);
        float valueDiff = from - to;

        return from + localPosition * valueDiff;
    }

    return defaultValue;
}

void Snake::generateItems() {

    for(unsigned int i = 0; i < itemsCount(); ++i) {

        SnakeItem* item = dynamic_cast<SnakeItem*>(factory());

        if (!item) {
            QuasarAppUtils::Params::log("The snake item class should be child class"
                                        " of the SnakeItem class.",
                                        QuasarAppUtils::Error);
            return;
        }

        float scale = getValueFromMap(_scales,
                                      static_cast<float>(i) / itemsCount());
        float lengthBIt = getValueFromMap(_lengthBetwinItemsMap,
                                          static_cast<float>(i) / itemsCount());

        item->setSize(item->size() * scale);
        item->setLengthBetwinItems(lengthBIt);

        add(item);
    }
}

const QMap<float, float> &Snake::lengthBetwinItemsMap() const {
    return _lengthBetwinItemsMap;
}

void Snake::setLengthBetwinItemsMap(const QMap<float, float> &newLengthBetwinItemsMap) {
    _lengthBetwinItemsMap = newLengthBetwinItemsMap;
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

unsigned int Snake::itemsCount() const {
    return 50;
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

}
