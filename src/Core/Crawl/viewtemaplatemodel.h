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
public:
    ViewTemaplateModel(const QString& viewTempalte, QObject *ptr = nullptr);

    /**
     * @brief viewTemplate This is path to the qml file with gui implementation of this model class.
     * @return path to the qml file with gui implementation of this model class.
     */
    const QString& viewTemplate() const;

private:
    QString _viewTemplate;
};

}
#endif // VIEWTEMAPLATEMODEL_H
