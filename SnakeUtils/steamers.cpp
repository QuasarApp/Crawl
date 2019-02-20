#include "steamers.h"

#include <QDataStream>

bool Steamers::baseRead(QDataStream &stream, QVariantMap &map) {
    unsigned int id;

    stream >> id;
    map["id"] = id;

    return id;
}

bool Steamers::baseWrite(QDataStream &stream, const QVariantMap &map) {
    unsigned int id = map.value("id", 0).toUInt();
    stream << id;

    return id;
}

bool Steamers::read(QDataStream &stream, QVariantMap &map, Steamers::Type type) {
    switch (type) {
    case Snake : {
        if (baseRead(stream, map)) {
            return false;
        };

        unsigned char spead;
        QList<float> skillet;

        stream >> spead;
        stream >> skillet;
        QVariantList varList;

        for (auto i : skillet) {
            varList.push_back(i);
        }

        map["class"] = Snake;
        map["spead"] = spead;
        map["skillet"] = varList;

        return stream.status() == QDataStream::Ok ||
               stream.status() == QDataStream::ReadPastEnd;
    }

    case Player : {
        if (!baseRead(stream, map)) {
            return false;
        }

        QString name;
        QString gmail;
        unsigned int maney;
        unsigned int record;
        QList<unsigned int> items;
        unsigned int currentSnake;

        stream >> name;
        stream >> gmail;
        stream >> maney;
        stream >> record;
        stream >> items;
        stream >> currentSnake;
        QVariantList varList;

        for (auto i : items) {
            varList.push_back(i);
        }

        map["name"] = name;
        map["gmail"] = gmail;
        map["maney"] = maney;
        map["record"] = record;
        map["items"] = varList;
        map["currentSnake"] = currentSnake;

        return stream.status() == QDataStream::Ok ||
               stream.status() == QDataStream::ReadPastEnd;
    }

    case Map : {
        return true;
    }

    case Game : {
        return true;
    }

    default: return false;
    }
}

bool Steamers::write(QDataStream &stream, const QVariantMap &map, Steamers::Type type) {
    switch (type) {
    case Snake : {
        if (baseWrite(stream, map)) {
            return false;
        };

        stream << static_cast<quint8>(map.value("spead").toUInt());

        QList<float> skillet;
        auto varList = map.value("skillet").toList();
        for (auto &&i : varList) {
            skillet.push_back(i.toFloat());
        }

        stream << skillet;

        return stream.status() == QDataStream::Ok ||
               stream.status() == QDataStream::ReadPastEnd;
    }

    case Player : {
        if (!baseWrite(stream, map)) {
            return false;
        }

        stream << map.value("name").toString();
        stream << map.value("gmail").toString();
        stream << map.value("maney").toUInt();
        stream << map.value("record").toUInt();

        QList<unsigned int> items;
        auto varList = map.value("items").toList();
        for (auto &&i : varList) {
            items.push_back(i.toUInt());
        }
        stream << items;

        stream << map.value("currentSnake").toUInt();

        return stream.status() == QDataStream::Ok ||
               stream.status() == QDataStream::ReadPastEnd;

    }

    case Map : {
        return true;
    }

    case Game : {
        return true;
    }

    default: return false;
    }

}

bool Steamers::isGeneralObject(Steamers::Type t) {
    return t & Steamers::GeneralObject;
}
