#ifndef ICONTROL_H
#define ICONTROL_H

#include <QObject>
#include "global.h"

/**
 * @brief The IControl class This interface should be contains implementation of custom user interface
 *  How to use this class:
 *  * inherit of this class
 *  * add to you class neede signals
 *  * subscribe to your signals in your world class and your qml interface class.
 *  For more information see the DefaultControl class.
 *
 */
class SNAKEPROJECT_EXPORT IControl : public QObject
{
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
    const QString &view() const;
signals:
    void viewChanged();

private:

    /**
     * @brief init This method intialize this object.
     * @note do not invoke this method monualy.
     * @return true if initialize finished succesfful
     */
    bool init();

    /**
     * @brief setView This method sets new value of qml view element
     * @param newView path to qml view.
     */
    void setView(const QString &newView);

    QString _view;

    friend class Engine;
};

#endif // ICONTROL_H
