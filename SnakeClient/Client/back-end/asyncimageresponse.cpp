#include "asyncimageresponse.h"

AsyncImageResponse::AsyncImageResponse() = default;
AsyncImageResponse::~AsyncImageResponse() = default;

QQuickTextureFactory *AsyncImageResponse::textureFactory() const {
    return _texture;
}

void AsyncImageResponse::setResult(const QImage& image) {
    _texture = QQuickTextureFactory::textureFactoryForImage(image);
    emit finished();
    deleteLater();
}
