#include <QtTest>
#include <cp.h>
#include <sp.h>
#include <thread>
#include <quasarapp.h>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <sqldbwriter.h>
#include <snake.h>

#include "factorynetobjects.h"

// add necessary includes here

class testSankeServer : public QObject
{
    Q_OBJECT

private:
    void testPingServerProtockol();
    void testStateServerProtockol();
    void testBanServerProtockol();
    void testUnBanServerProtockol();
    void testRestartServerProtockol();

    void testPingClientProtockol();
    void testLogin();
    void testUserData();
    void testGetItem();
    void testApplyData();


public:
    testSankeServer();
    void testSql();
    ~testSankeServer();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testServerProtockol();
    void testClientProtockol();



};

testSankeServer::testSankeServer()
{

}

testSankeServer::~testSankeServer()
{

}

void testSankeServer::initTestCase()
{
    ClientProtocol::initClientProtockol();
}

void testSankeServer::cleanupTestCase()
{

}

void testSankeServer::testPingServerProtockol()
{
    QuasarAppUtils::Params::setEnable("verbose", true);

    int argc =0;
    char * argv[] = {nullptr};

    QCoreApplication app(argc, argv);

    auto serv = new ServerProtocol::Server(this);

    QVERIFY(serv->run(DEFAULT_SERVER));

    auto client = new ServerProtocol::Client(this);

    bool isWork = false;
    QObject::connect(client, &ServerProtocol::Client::sigIncommingData,
                     [&isWork, &app] (const QVariantMap& map) {

        isWork = map["res"].toString() == "Pong";
        app.exit(0);

    });

    QVERIFY(client->ping());

    QTimer::singleShot(1000, [&app](){
        app.exit(0);
    });

    app.exec();

    QVERIFY(isWork);

    delete serv;
    delete client;

}

void testSankeServer::testStateServerProtockol()
{
    ServerProtocol::Client cle;
    QVERIFY(cle.getState());
}

void testSankeServer::testBanServerProtockol()
{
    ServerProtocol::Client cle;
    QVERIFY(!cle.ban(QHostAddress()));

    QVERIFY(cle.ban(QHostAddress("192.192.192.192")));
}

void testSankeServer::testUnBanServerProtockol()
{
    ServerProtocol::Client cle;
    QVERIFY(!cle.unBan(QHostAddress()));

    QVERIFY(cle.unBan(QHostAddress("192.192.192.192")));
}

void testSankeServer::testRestartServerProtockol()
{
    ServerProtocol::Client cle;
    QVERIFY(!cle.restart("lolo", 0));

    QVERIFY(!cle.restart("192.168.1.999", 0));
    QVERIFY(!cle.restart("192.168.1.99", 0));
    QVERIFY(!cle.restart("192.168.1.9", 0));

    QVERIFY(!cle.restart("-1.168.1.999", 77));
    QVERIFY(!cle.restart("192.168.-1.99", 7777));

    QVERIFY(cle.restart("192.168.1.9", 3456));

}

void testSankeServer::testPingClientProtockol() {

    QuasarAppUtils::Params::setEnable("verbose", true);

    int argc = 0;
    char * argv[] = {nullptr};

    QCoreApplication app(argc, argv);

    auto serv = new ClientProtocol::Server(this);

    QVERIFY(serv->run(LOCAL_SNAKE_SERVER, DEFAULT_SNAKE_PORT));

    auto client = new ClientProtocol::Client(this);

    bool isWork = false;
    QObject::connect(client, &ClientProtocol::Client::sigIncommingData,
                     [&isWork, &app] (const ClientProtocol::Command cmd,
                     const QByteArray&) {

        isWork = cmd == ClientProtocol::Command::Ping;
        app.exit(0);

    });

    QVERIFY(client->ping());

    QTimer::singleShot(1000, [&app](){
        app.exit(0);
    });

    app.exec();

    QVERIFY(isWork);

    delete serv;
    delete client;
}

void testSankeServer::testLogin() {
    ClientProtocol::Client cle;

    auto pass = QCryptographicHash::hash("testpass", QCryptographicHash::Sha512);
    QVERIFY(!cle.login("Test@gmail.com", pass));

    pass = QCryptographicHash::hash("testpass", QCryptographicHash::Sha256);
    QVERIFY(cle.login("Test@gmail.com", pass));

}

void testSankeServer::testUserData() {
    ClientProtocol::Client cle;

    QVERIFY(!cle.updateData());

    auto token = QCryptographicHash::hash("testtoken", QCryptographicHash::Sha256);
    cle._token = token;
    cle._online = true;

    QVERIFY(cle.updateData());
}

void testSankeServer::testGetItem() {

    ClientProtocol::Client cle;

    QVERIFY(!cle.updateData());

    auto token = QCryptographicHash::hash("testtoken", QCryptographicHash::Sha256);
    cle._token = token;
    cle._online = true;

    QVERIFY(cle.getItem(1));
}

void testSankeServer::testApplyData() {

    ClientProtocol::Client cle;


    auto token = QCryptographicHash::hash("testtoken", QCryptographicHash::Sha256);
    cle._token = token;
    cle._online = true;

    QVERIFY(!cle.savaData(QList<int>()));

    QList<int> listData = {1};

    QVERIFY(cle.savaData(listData));


}

void testSankeServer::testSql() {
    SqlDBWriter db;
    QFile::remove("./test.db");

    bool init = db.initDb("test.db", "./");

    if (!init) {
        QFile::remove("./test.db");
    }

    QVERIFY(init);

    ClientProtocol::Snake snake;
    snake.setSpeed(10);
    snake.setSkillet(QList<float>() << 1);
    snake.setSnakeClass(0);


    // TEST ITEM

    ClientProtocol::Snake *resSnake;

    QVERIFY(db.saveItem(&snake) < 0);
    snake.setId(0);
    int id = db.saveItem(&snake);

    QVERIFY(id == 0);
    resSnake = static_cast<decltype (resSnake)>(db.getItem(id));
    QVERIFY(resSnake);
    QVERIFY(snake.getSpeed() == resSnake->getSpeed());
    QVERIFY(snake.getSkillet() == resSnake->getSkillet());
    QVERIFY(snake.getSnakeClass() == resSnake->getSnakeClass());
    QVERIFY(snake.getClass() == resSnake->getClass());
    QVERIFY(snake.id() == resSnake->id());

    resSnake->setSnakeClass(10);
    QVERIFY(id == db.saveItem(resSnake));

    auto temp = static_cast<decltype (resSnake)>(db.getItem(id));

    QVERIFY(temp->getSnakeClass() == 10);

    delete temp;
    delete resSnake;


//    // TEST PLAYER

//    QVariantMap tempPlayer;

//    QVERIFY(ClientProtocol::FactoryNetObjects::build(
//                ClientProtocol::NetworkClasses::Player, tempPlayer));

//    QVERIFY(ClientProtocol::FactoryNetObjects::fillRandomData(tempPlayer));

//    QVariantMap resPlayer;

//    QVERIFY(db.saveItem(tempPlayer) < 0);
//    tempPlayer["id"] = 0;
//    QVERIFY(db.saveItem(tempPlayer) < 0);

//    tempPlayer["items"] = QVariantList() << 0;
//    tempPlayer["currentSnake"] = 0;

//    id = db.savePlayer(tempPlayer);

//    QVERIFY(id == 0);
//    QVERIFY(db.getPlayer(id, resPlayer));
//    QVERIFY(tempPlayer.size() == resPlayer.size());

//    for (auto &key :tempPlayer.keys()) {
//        QVERIFY(tempPlayer.value(key).toString() == resPlayer.value(key).toString());
//    }

////    list = tempPlayer["skillet"].toList();
////    list[1] = 100;
////    tempItem["skillet"] = list;

////    QVERIFY(db.saveItem(tempItem) == 0);
////    QVERIFY(db.getItem(id, resItem));

////    QVERIFY(resItem["skillet"].toList()[1] == 100);

////    QVERIFY(tempItem.size() == resItem.size());

////    for (auto &key :tempItem.keys()) {
////        QVERIFY(tempItem.value(key).toString() == resItem.value(key).toString());
////    }

}

void testSankeServer::testServerProtockol() {
    testPingServerProtockol();

    auto serv = new ServerProtocol::Server(this);
    QVERIFY(serv->run(DEFAULT_SERVER));
    testStateServerProtockol();
    testBanServerProtockol();
    testUnBanServerProtockol();
    testRestartServerProtockol();
}

void testSankeServer::testClientProtockol() {
    testPingClientProtockol();

    auto serv = new ClientProtocol::Server(this);
    QVERIFY(serv->run(LOCAL_SNAKE_SERVER, DEFAULT_SNAKE_PORT));

    testLogin();
    testGetItem();
    testUserData();
    testApplyData();
    testSql();
}

QTEST_APPLESS_MAIN(testSankeServer)

#include "tst_testsnakeserver.moc"
