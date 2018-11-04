#include "guiobject.h"

GuiObject::GuiObject(QObject *ptr):
    QObject (ptr) {
    generateId();

}

double GuiObject::angle() const {
    return m_angle;
}

QString GuiObject::texture() const {
    return m_texture;
}

void GuiObject::render() {

}

QRectF GuiObject::rect() const {
    return m_rect;
}

QRectF& GuiObject::getRect() {
    return m_rect;
}

void GuiObject::setAngle(double angle) {

    m_angle = angle;
    emit angleChanged(m_angle);
}

int GuiObject::guiId() const {
    return m_guiId;
}

void GuiObject::setRect(QRectF rect) {
    if (m_rect == rect)
        return;

    m_rect = rect;
    emit rectChanged(m_rect);
}

void GuiObject::generateId() {
    static int id = 0;
    m_guiId = id++;
}

void GuiObject::setTexture(const QString &texture) {
    m_texture = texture;
    emit textureChanged(m_texture);
}


