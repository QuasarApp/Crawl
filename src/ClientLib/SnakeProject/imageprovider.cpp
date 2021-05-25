#include "asyncimageresponse.h"
#include "imageprovider.h"
#include <QQuickImageResponse>
#include <QtConcurrent>

ImageProvider::ImageProvider() = default;
ImageProvider::~ImageProvider() = default;

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

    QtConcurrent::run(readImage);

    return response;
}



