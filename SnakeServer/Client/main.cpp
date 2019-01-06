#include <QCoreApplication>
#include <quasarapp.h>
#include <client.h>
#include <QDebug>

//QString parseQvariant( const QVariant& data) {
//    QString res;

//    /*
//     *
//     *
//     *
//     *         Invalid = QMetaType::UnknownType,
//        Bool = QMetaType::Bool,
//        Int = QMetaType::Int,
//        UInt = QMetaType::UInt,
//        LongLong = QMetaType::LongLong,
//        ULongLong = QMetaType::ULongLong,
//        Double = QMetaType::Double,
//        Char = QMetaType::QChar,
//        Map = QMetaType::QVariantMap,
//        List = QMetaType::QVariantList,
//        String = QMetaType::QString,
//        StringList = QMetaType::QStringList,
//*/

//    switch (data.type()) {
//    case QMetaType::Bool: {
//        res = (data.c)?
//        break;
//    }
//    default: res = "UnknownType";
//    }

//    return res;
//}


void handleResponcke(const QVariantMap &data) {
    for(auto iter = data.begin(); iter != data.end(); ++iter) {
      qInfo() << QString("%0: %1").arg( iter.key()).arg(iter.value().toString());
    }

    QCoreApplication::exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QuasarAppUtils::Params::parseParams(argc, argv);

    ServerProtocol::Client cli;

    QObject::connect(&cli, &ServerProtocol::Client::sigIncommingData,
                     &handleResponcke);

    if (QuasarAppUtils::Params::isEndable("ping")) {
        ServerProtocol::Package pkg;
        pkg.hdr.command = ServerProtocol::ping;
        if (!cli.sendPackage(pkg)) {
            qCritical() << "command not sendet!";
            return 1;
        }
    } else {
       return 0;
    }

    return a.exec();
}
