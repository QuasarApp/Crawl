#ifndef HEAD_H
#define HEAD_H
#define TO_RADIAN 0.017453293


#include "guiobject.h"
#include <QString>

class Head : public GuiObject
{
private:
    qint64 time;
    double *speed;
    const int megaFastSpead = 200;
    const int fastSpead = 100;
    const int normSpead = 50;

    const QString generalSpeadColor = "#616a6b";
    const QString normSpeadColor = "#5d6d7e";
    const QString fastSpeadColor = "#eb984e";
    const QString megaFastSpeadColor = "#ec7063";

public:
    Head(double x , double y, double h, double w, double *speed);
    void setAngle(double angle);
    void render() override;
    void reset() override;
    void unPause();
    ~Head() override;
};

#endif // HEAD_H
