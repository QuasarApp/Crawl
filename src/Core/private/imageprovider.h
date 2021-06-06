#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>
#include <QPixmap>

class ImageProvider: public QQuickAsyncImageProvider
{
private:
public:
    explicit ImageProvider();
    ~ImageProvider() override;

    QQuickImageResponse *requestImageResponse(const QString &id,
                                              const QSize &requestedSize) override;
};


#endif // IMAGEPROVIDER_H
