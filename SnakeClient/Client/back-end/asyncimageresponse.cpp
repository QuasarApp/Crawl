#include "asyncimageresponse.h"

AsyncImageResponse::AsyncImageResponse() = default;
AsyncImageResponse::~AsyncImageResponse() = default;

QQuickTextureFactory *AsyncImageResponse::textureFactory() const {
    return _texture;
}

// memory leak ?
void AsyncImageResponse::setResult(const QImage& image) {
    _texture = QQuickTextureFactory::textureFactoryForImage(image);
    emit finished();
//    deleteLater();
}

void AsyncImageResponse::error(const QString &err) {
    _errorString = " " + err;
}

QString AsyncImageResponse::errorString() const {
    return QQuickImageResponse::errorString() + _errorString;
}
