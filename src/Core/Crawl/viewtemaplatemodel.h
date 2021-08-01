//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef VIEWTEMAPLATEMODEL_H
#define VIEWTEMAPLATEMODEL_H

#include "global.h"
#include <QObject>

namespace CRAWL {

/**
 * @brief The ViewTemaplateModel class This is base class for supporting model view template in qml.
 * This class is base model og the view objects.
 * All qml viewObjects will be generated using the ViewTemaplateModel::viewTemplate method on The main QML scane.
 *
 */
class CRAWL_EXPORT ViewTemaplateModel: public QObject
{
    Q_OBJECT

    /**
     * @brief viewTemplate This is path to the qml file with gui implementation of this model class.
     */
    Q_PROPERTY(QString viewTemplate READ viewTemplate)

    /**
     * @brief viewObject This is object of view companent.
     * @note If the object not inited and the model propetye of the view is empty then this property will be equals nullptr
    */
    Q_PROPERTY(QObject *viewObject READ viewObject WRITE setViewObject NOTIFY viewObjectChanged)
public:

    ViewTemaplateModel(const QString& viewTempalte,
                       QObject *ptr = nullptr);

    /**
     * @brief viewTemplate This is path to the qml file with gui implementation of this model class.
     * @return path to the qml file with gui implementation of this model class.
     */
    const QString& viewTemplate() const;

    /**
     * @brief viewObject This is object of view companent.
     * @note For working with the view propertyes use the QOBject::getPropertye and QObject::setPropertye methods. For invoke view method use the "QMetaObject::invokeMethod" method.
     * For get more inforamtion about qt method see the Qt documentation.
     * @return pointer to view object.
     * @note If the object not inited and the model propetye of the view is empty then this property will be equals nullptr
    */
    QObject *viewObject() const;

    /**
     * @brief setViewObject This method sets new value of the ViewObject. This method will be invoked automaticly.
     * @param newViewObject This is new valur of the view object.
     */
    void setViewObject(QObject *newViewObject);

signals:
    void viewObjectChanged();

private:
    QString _viewTemplate;
    QObject *_viewObject = nullptr;
};

}
#endif // VIEWTEMAPLATEMODEL_H
