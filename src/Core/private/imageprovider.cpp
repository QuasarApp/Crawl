//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "asyncimageresponse.h"
#include "imageprovider.h"
#include <QQuickImageResponse>
#include <QtConcurrent>

ImageProvider::ImageProvider() = default;
ImageProvider::~ImageProvider() = default;

#define IgnoreQFuture(x) x.isRunning()

QQuickImageResponse *ImageProvider::requestImageResponse(const QString &id,
                                                         const QSize &requestedSize) {

    AsyncImageResponse* response = new AsyncImageResponse();
    auto readImage = [id, requestedSize, response]() mutable {
        Q_UNUSED(requestedSize);

        auto params = id.split("/");

        if (params.contains("player")) {
            response->setResult(QImage(":/img/defaultuser").
                                scaled(requestedSize, Qt::KeepAspectRatioByExpanding));

        } else if (params.contains("item")) {
            response->setResult(QImage(":/img/defaultsnake").
                                scaled(requestedSize, Qt::KeepAspectRatioByExpanding));
        } else {
            response->error("Wrong first parametr example 'first/last'");
        }

    };

    IgnoreQFuture(QtConcurrent::run(readImage));

    return response;
}



