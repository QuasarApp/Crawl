#include "guiobject.h"

GuiObject::GuiObject(const QString &viewTempalte, QObject *ptr):
    QObject (ptr) {
    m_viewTemplate = viewTempalte;
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
    return QRectF(m_x - m_w / 2, m_y - m_h / 2, m_w, m_h);
}

void GuiObject::setAngle(double angle) {
    m_angle = angle;
    emit angleChanged(m_angle);
}

int GuiObject::guiId() const {
    return m_guiId;
}

QString GuiObject::color() const {
    return m_color;
}

void GuiObject::setColor(QString color) {
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(m_color);
}

double GuiObject::x() const {
    return m_x;
}

double GuiObject::y() const {
    return m_y;
}

double GuiObject::w() const {
    return m_w;
}

double GuiObject::h() const {
    return m_h;
}

void GuiObject::generateId() {
    static int id = 0;
    m_guiId = id++;
}

void GuiObject::setH(double h) {
    m_h = h;
    emit hChanged(m_h);
}

void GuiObject::reset() {
    setX(-1);
    setY(-1);
}

int GuiObject::radius() const {
    return m_radius;
}

QString GuiObject::viewTemplate() const {
    return m_viewTemplate;
}

void GuiObject::setRadius(int radius) {
    if (m_radius == radius)
        return;

    m_radius = radius;
    emit radiusChanged(m_radius);
}

void GuiObject::setW(double w) {
    m_w = w;
    emit wChanged(m_w);

}

void GuiObject::setY(double y) {
    m_y = y;
    emit yChanged(m_y);

}

void GuiObject::setX(double x) {
    m_x = x;
    emit xChanged(m_x);

}

void GuiObject::setTexture(const QString &texture) {
    m_texture = texture;
    emit textureChanged(m_texture);
}


