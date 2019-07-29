#include "asyncimageresponse.h"
#include "imageprovider.h"
#include <QQuickImageResponse>
#include <QtConcurrent>

ImageProvider::ImageProvider() = default;
ImageProvider::~ImageProvider() = default;

QQuickImageResponse *ImageProvider::requestImageResponse(const QString &id,
                                                         const QSize &requestedSize) {

    Q_UNUSED(id);
    AsyncImageResponse* response = new AsyncImageResponse();

    auto readImage = [requestedSize, response]() mutable {
        Q_UNUSED(requestedSize);
        response->setResult(QImage(":/img/defaultuser").scaled(requestedSize));
    };

    QtConcurrent::run(readImage);

    return response;
}



