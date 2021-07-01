//#
//# Copyright (C) 2020-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "clasterstest.h"
#include <QtTest>
#include <Extensions/claster.h>
#include <Crawl/clasteritem.h>
#include <Crawl/singleclasterworlditem.h>
#include <Crawl/iworld.h>

// Test claster object.
class TestClasterObject: public IWorldItem, public Claster {

public:
    TestClasterObject(): IWorldItem("TestClaster"){};
protected:
    void onIntersects(const IWorldItem *) {};
};

// Test single claster item
class TestClasterSingleItem: public SingleClasterWorldItem {
public:
    TestClasterSingleItem(): SingleClasterWorldItem("TestClasterSingleItem"){};
protected:
    void onIntersects(const IWorldItem *) {};
};

// Test claster item
class TestClasterItem: public ClasterItem {
public:
    TestClasterItem(): ClasterItem("TestClasterItem"){};
protected:
    void onIntersects(const IWorldItem *) {};
};

// Test world of clasters
class TestWorld: public IWorld {
public:
    TestWorld(): IWorld(){};

    // IWorld interface
public:
    IPlayer *initPlayer() const {return nullptr;};
    WorldRule *initWorldRules() {return nullptr;};
    QString initHdrBackGround() const {return "";};
    QString description() const {return "";};
    QString imagePreview() const {return "";};
    QString name() const {return "TestWorld";};
    int costToUnlock() const {return 0;};

    friend class ClastersTest;
};

ClastersTest::ClastersTest() {

}

void ClastersTest::test() {
    // test clasters
    testOneClaster();
    testClastersWithWorld();
}

void ClastersTest::testOneClaster() const {
    TestClasterItem item;
    TestClasterSingleItem singleItem;

    // life of the clasters
    {
        TestClasterObject claster, claster2;

        // Add items to first clasters
        claster.add(&item);
        claster.add(&singleItem);

        // in the first claster should be 2 objects
        QVERIFY(claster.objects().size() == 2);

        // item sould be contains oly one parents claster object.
        QVERIFY(item.parentClastersCount() == 1);
        QVERIFY(singleItem.parentClastersCount() == 1);

        // Add items into second claster object
        claster2.add(&item);
        claster2.add(&singleItem);

        // in the second claster should be 2 objects
        QVERIFY(claster2.objects().size() == 2);
        // but first claster should be contains only one claster item because the singleclater item cannot are child of the two clasters.
        QVERIFY(claster.objects().size() == 1);

        // item sould be contains two parents claster object.

        QVERIFY(item.parentClastersCount() == 2);
        // item sould be contains oly one parents claster object.
        QVERIFY(singleItem.parentClastersCount() == 1);
    }

    // after distrou clasters objects the parents list size should be equals 0
    QVERIFY(item.parentClastersCount() == 0);
    QVERIFY(singleItem.parentClastersCount() == 0);

}

void ClastersTest::testClastersWithWorld() const {
    TestWorld world;
    TestClasterObject *claster = new TestClasterObject(),
            *claster2 = new TestClasterObject();

    TestClasterItem *item = new TestClasterItem(),
            *item2 = new TestClasterItem;

    // Add to first claster two items.
    claster->add(item);
    claster->add(item2);

    // The claster 2 contains item 2 only.
    claster2->add(item2);

    // Add claster item to world
    world.addItem(claster);

    // After adding claster object ito world child objects should be addeed automaticaly
    QVERIFY(world._items.size() == 3);

    // add second claster ot world
    world.addItem(claster2);

    QVERIFY(world._items.size() == 4);

    // remove claster with 2 items from world
    world.removeItem(claster->guiId());

    // after removing claster ovject child items should be removed too. but ony items that contains one parent claster.
    QVERIFY(world._items.size() == 2);

    world.removeItem(claster2->guiId());

}
