//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ASYNCIMAGERESPONSE_H
#define ASYNCIMAGERESPONSE_H

#include <QQuickImageResponse>


class AsyncImageResponse : public QQuickImageResponse {

private:
    QQuickTextureFactory *_texture = nullptr;
    QString _errorString;
public:

    AsyncImageResponse ();
    ~AsyncImageResponse () override;

    QQuickTextureFactory *textureFactory() const override;

    void setResult(const QImage &image);
    void error(const QString &err);

    QString errorString() const override;
};
#endif // ASYNCIMAGERESPONSE_H
