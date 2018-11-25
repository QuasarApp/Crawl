#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "baseclass.h"
#include "QObject"

#include <QRectF>

class GuiObject:public QObject, public BaseClass
{
    Q_OBJECT
// @todo: add color
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double angle READ angle NOTIFY angleChanged)
    Q_PROPERTY(QString texture READ texture NOTIFY textureChanged)
    Q_PROPERTY(int guiId READ guiId NOTIFY guiIdChanged)

    Q_PROPERTY(double x READ x NOTIFY xChanged)
    Q_PROPERTY(double y READ y NOTIFY yChanged)
    Q_PROPERTY(double w READ w NOTIFY wChanged)
    Q_PROPERTY(double h READ h NOTIFY hChanged)

private:
    void generateId();

protected:
    int m_guiId;
    double m_angle;
    QString m_texture;
    QString m_color;

    double m_x;
    double m_y;
    double m_w;
    double m_h;

    void setTexture(const QString &texture);


public:
    GuiObject(QObject *ptr = nullptr);

    double angle() const;
    QString texture() const;

    void render();

    QRectF rect() const;
    virtual void setAngle(double angle);
    int guiId() const;

    QString color() const;

    void setColor(QString color);

    double x() const;
    double y() const;
    double w() const;
    double h() const;

    void setX(double x);
    void setY(double y);
    void setW(double w);
    void setH(double h);

signals:
    void angleChanged(double angle);
    void textureChanged(QString texture);
    void guiIdChanged(int guiId);
    void colorChanged(QString color);
    void xChanged(double x);
    void yChanged(double y);
    void wChanged(double w);
    void hChanged(double h);
};

#endif // GUIOBJECT_H
