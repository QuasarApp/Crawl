//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "groupobjecttest.h"
#include "Crawl/groupobject.h"

#include <Crawl/clasteritem.h>

class TestGroupObject: public CRAWL::IWorldItem, public CRAWL::GroupObject {

public:

    // IWorldItem interface
    TestGroupObject(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {

    }

    // IRender interface
    void render(unsigned int tbfMsec) override {
        GroupObject::render(tbfMsec);
    };

    void init() override {};

    friend  GroupObjectTest;
};

class TestGroupObjectItem: public CRAWL::ClasterItem {

public:
    // IWorldItem interface

    TestGroupObjectItem(): CRAWL::ClasterItem(AUTO_CLASS_NAME) {

    }
};

GroupObjectTest::GroupObjectTest() {

}

void GroupObjectTest::test() {
    testBehavior();
}

void GroupObjectTest::testBehavior() const {
    TestGroupObject object;
    TestGroupObjectItem item;

    object.setposition({100, 100, 0});
    object.setRotation(QQuaternion::fromEulerAngles(100,0,0));

    object.installObject(&item);

    // check if added object after install into claster or not
    QVERIFY(object.objects().size() == 1);

    // The rotation and position of the main and child classes should be defferent
    QVERIFY(item.position() != object.position());
    QVERIFY(item.rotation() != object.rotation());

    object.render(0);

    // after invoke the render function all positions and rotations should be changed
    QVERIFY(item.position() == object.position());
    QVERIFY(item.rotation() == object.rotation());

    QVector3D localPosition = {10,0,0};
    QQuaternion localRotation = QQuaternion::fromEulerAngles(0,5,0);

    object.updateRotation(item.guiId(), localRotation);
    object.render(0);
    // after invoke the render function all positions and rotations should be changed
    QVERIFY(item.rotation() == (object.rotation() * localRotation));

    object.updatePosition(item.guiId(), localPosition);
    object.setRotation(QQuaternion::fromEulerAngles(0,0,0));

    object.render(0);
    QVERIFY(item.position() == (object.position() + localPosition));


    object.remove(&item);

    QVERIFY(object.objects().size() == 0);


}
