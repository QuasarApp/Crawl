#ifndef ICONTROL_H
#define ICONTROL_H
#include <QObject>

To- To create a view for control

/**
 * @brief The IControl class This interface should be contains implementation of custom user interface
 */
class IControl : public QObject
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

    /**
     * @brief gameActionEvent Invoke This method if you want to send event to qml.
     */
    void gameActionEvent(int actionID) const;
signals:
    void viewChanged();

    /**
     * @brief sigAction Emit this signal in qml file and handle on cpp world file.
     * @param actionId
     */
    void sigAction(int actionId);

    /**
     * @brief actionEvent Handle this evnt on qml file.
     * @code{qml}
     * Obejct{
     *
     *     onActionEvent {
     *         console.log(actionID);
     *     }
     * }
     *
     */
    void actionEvent(int actionID);

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
