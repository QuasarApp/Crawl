#ifndef ICONTROL_H
#define ICONTROL_H
#include <QObject>

/**
 * @brief The IControl class This interface should be contains implementation of custom user interface
 */
class IControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString view READ view WRITE setView NOTIFY viewChanged)

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
     * @return
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
