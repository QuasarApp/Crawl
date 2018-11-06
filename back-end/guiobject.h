#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "baseclass.h"
#include "QObject"

#include <QRectF>

class GuiObject:public QObject, public BaseClass
{
    Q_OBJECT

    Q_PROPERTY(double angle READ angle NOTIFY angleChanged)
    Q_PROPERTY(QString texture READ texture NOTIFY textureChanged)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect NOTIFY rectChanged)
    Q_PROPERTY(int guiId READ guiId NOTIFY guiIdChanged)

private:
    void generateId();

protected:
    int m_guiId;
    double m_angle;
    QString m_texture;
    QRectF m_rect;

    void setTexture(const QString &texture);
    void setRect(QRectF rect);


public:
    GuiObject(QObject *ptr = nullptr);

    double angle() const;
    QString texture() const;

    void render();

    QRectF rect() const;
    QRectF &getRect();
    void setAngle(double angle);
    int guiId() const;

signals:
    void angleChanged(double angle);
    void textureChanged(QString texture);
    void rectChanged(QRectF rect);
    void guiIdChanged(int guiId);
};

#endif // GUIOBJECT_H
