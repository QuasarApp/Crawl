//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef PREVIEWCONTROL_H
#define PREVIEWCONTROL_H

#include "icontrol.h"

namespace CRAWL {

/**
 * @brief The PreviewControl class This is base class of the preview popup control.
 */
class CRAWL_EXPORT PreviewControl: public IControl
{
    Q_OBJECT
public:
    PreviewControl();
    QString initQmlView() const override;

signals:

    /**
     * @brief start emited when user click start button from the preview menu.
     */
    void start();

    /**
     * @brief mousePositionChanged This signal emited when user true change the preview postion
     * @param x delta by x axis
     * @param y delta by y axis
     */
    void mousePositionChanged(double x, double y);

    /**
     * @brief select This signal emited when user select new item on hew own inventary.
     * @param id This is id of the selected item
     * @param isSelected this is bool option for set selected or diselected.
     */
    void select(int id, bool isSelected);

};
}
#endif // PREVIEWCONTROL_H
