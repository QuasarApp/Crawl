#include "imageprovider.h"

ImageProvider::ImageProvider(): QQuickAsyncImageProvider() {

}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size,
                                     const QSize &requestedSize) {

    bool ok;
    int user = id.toShort(&ok);

    if(!ok) {
        *size = QSize(1,1);
        return QPixmap(1,1);
    }

    short width = 100;
    short height = 50;

    QPixmap result;

    if (size)
        *size = QSize(width, height);

    if(user){
       return QPixmap(":/img/defaultuser").scaled(requestedSize);
    }

    return result.scaled(requestedSize);
}
