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
    Q_PROPERTY(QString viewTemplate READ viewTemplate NOTIFY viewTemplateChanged)
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)

    Q_PROPERTY(double x READ x NOTIFY xChanged)
    Q_PROPERTY(double y READ y NOTIFY yChanged)
    Q_PROPERTY(double w READ w NOTIFY wChanged)
    Q_PROPERTY(double h READ h NOTIFY hChanged)

private:
    void generateId();
    QString m_viewTemplate;

protected:
    int m_guiId = -1;
    double m_angle = 0;
    QString m_texture = "";
    QString m_color = "";
    int m_radius = 0;

    double m_x = 0;
    double m_y = 0;
    double m_w = 0;
    double m_h = 0;

    void setTexture(const QString &texture);


public:
    GuiObject(const QString& viewTempalte = "GraphicItem", QObject *ptr = nullptr);

    double angle() const;
    QString texture() const;

    void render() override;

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

    virtual void reset();
    int radius() const;
    QString viewTemplate() const;

public slots:

    void setRadius(int radius);

signals:
    void angleChanged(double angle);
    void textureChanged(QString texture);
    void guiIdChanged(int guiId);
    void colorChanged(QString color);
    void xChanged(double x);
    void yChanged(double y);
    void wChanged(double w);
    void hChanged(double h);
    void radiusChanged(int radius);
    void viewTemplateChanged(QString viewTemplate);
};

#endif // GUIOBJECT_H
