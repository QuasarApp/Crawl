#include "guiobject3d.h"


GuiObject3D::GuiObject3D(const QString &viewTempalte, QObject *ptr):
    GuiObject(viewTempalte, ptr) {

}

double GuiObject3D::z() const {
    return _z;
}

double GuiObject3D::scaleZ() const {
    return _scaleZ;
}

void GuiObject3D::setZ(double z) {
    if (z == _z){
        return;
    }

    _z = z;
    emit zChanged();
}

void GuiObject3D::setScaleZ(double scaleFactor) {
    if (scaleFactor == _scaleZ){
        return;
    }

    _scaleZ = scaleFactor;
    emit scaleZChanged();
}

void GuiObject3D::setMash(const QString &mash) {
    if (mash == _mash){
        return;
    }

    _mash = mash;
    emit mashChanged();
}

QString GuiObject3D::mash() const {
    return _mash;
}

double GuiObject3D::scaleX() const {
    return h();
}

double GuiObject3D::scaleY() const {
    return w();
}
