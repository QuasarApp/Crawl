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
