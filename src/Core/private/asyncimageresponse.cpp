//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

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
