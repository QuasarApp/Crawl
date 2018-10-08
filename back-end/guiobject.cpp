#include "guiobject.h"

GuiObject::GuiObject(QObject *ptr) :
    QObject (ptr)
{

}

double GuiObject::getAngle() const {
    return angle;
}

void GuiObject::setAngle(double angle) {
    this->angle = angle;
}

double GuiObject::getY() const {
    return y;
}

void GuiObject::setY(double y) {
    this->y = y;
}

double GuiObject::getX() const {
    return x;
}

void GuiObject::setX(double x) {
    this->x = x;
}

QString GuiObject::getTexture() const {
    return texture;
}

void GuiObject::setTexture(const QString &texture) {
    this->texture = texture;
}
