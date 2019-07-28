#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>
#include <QPixmap>

class ImageProvider: public QQuickAsyncImageProvider
{
private:
public:
    explicit ImageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size,
                          const QSize &requestedSize);
};


#endif // IMAGEPROVIDER_H
