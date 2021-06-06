#include "backgrounditem.h"

#include <QColor>

BackGroundItem::BackGroundItem(double x, double y):
    ItemWorld (x, y) {
    setBeckGroundObject(true);
    reset();
}

void BackGroundItem::reset() {
    auto tempColor = QColor(rand() % 255, rand() % 255, rand() % 255, 10);
    setColor(tempColor.name(QColor::HexArgb));
    auto radius = rand() % 200;
    setSize(radius , radius);

}
