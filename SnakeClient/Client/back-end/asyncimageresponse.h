#ifndef ASYNCIMAGERESPONSE_H
#define ASYNCIMAGERESPONSE_H

#include <QQuickImageResponse>


class AsyncImageResponse : public QQuickImageResponse {

private:
    QQuickTextureFactory *_texture = nullptr;

public:

    AsyncImageResponse ();
    ~AsyncImageResponse () override;

    QQuickTextureFactory *textureFactory() const override;

    void setResult(const QImage &image);
};
#endif // ASYNCIMAGERESPONSE_H
