//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CRAWL_ICONTROL_H
#define CRAWL_ICONTROL_H

#include <QObject>
#include "global.h"

namespace CRAWL {


/**
 * @brief The IControl class This interface should be contains implementation of custom user interface
 *  How to use this class:
 *  * inherit of this class
 *  * add to you class neede signals
 *  * subscribe to your signals in your world class and your qml interface class.
 *  For more information see the DefaultControl class.
 *
 */
class CRAWL_EXPORT IControl : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString view READ view NOTIFY viewChanged)

public:
    IControl();
    virtual ~IControl();

    /**
     * @brief initQmlView This method should be return path to qml view element.
     * @return path to qml view.
     */
    virtual QString initQmlView() const = 0;

    /**
     * @brief view This method retun qml view element.
     * @return return path to qml view.
     */
    const QString &view();

signals:
    void viewChanged();

private:
    /**
     * @brief setView This method sets new value of qml view element.
     * @param newView path to qml view.
     */
    void setView(const QString &newView);

    QString _view;

    friend class Engine;
};

}

#endif // CRAWL_ICONTROL_H
