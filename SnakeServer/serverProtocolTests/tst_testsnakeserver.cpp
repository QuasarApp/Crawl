#include <QtTest>
#include <cp.h>
#include <sp.h>
#include <thread>
#include <quasarapp.h>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <sqldbwriter.h>
#include <sqldbcache.h>

#include <snake.h>
#include <playerdbdata.h>

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

    void testBaseSql();
    void testSqlCache();

public:
    testSankeServer();

    ~testSankeServer();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testServerProtockol();
    void testClientProtockol();
    void testSql();


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

void testSankeServer::testBaseSql() {
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


    // TEST PLAYER

    PlayerDBData *player = new PlayerDBData();

    player->setMany(10);
    player->setLastOnline(1000);
    player->setOnlineTime(1001);
    player->setName("test");
    player->setGmail("test@gmail.com");
    player->setCureentSnake(0);
    player->setToken(QCryptographicHash::hash("1", QCryptographicHash::Sha256));

    QVERIFY(db.savePlayer(player) < 0);
    player->setId(0);

    QVERIFY(db.savePlayer(player) < 0);
    player->setCureentSnake(-1);
    id = db.savePlayer(player);
    QVERIFY(id == 0);

    QVERIFY(!db.saveowners(id, QSet<int>() << 1));
    QVERIFY(db.saveowners(id, QSet<int>() << 0));

    QSet<int> items;
    QVERIFY(db.getAllItemsOfPalyer(id, items));
    QVERIFY(items.contains(0));
    QVERIFY(items.size() == 1);


    player->setCureentSnake(0);
    id = db.savePlayer(player);

    auto resPlayer = static_cast<decltype (player)>(db.getPlayer(id));
    QVERIFY(resPlayer);
    QVERIFY(player->getLastOnline() == resPlayer->getLastOnline());
    QVERIFY(player->getMany() == resPlayer->getMany());
    QVERIFY(player->getOnlineTime() == resPlayer->getOnlineTime());
    QVERIFY(player->getName() == resPlayer->getName());
    QVERIFY(player->getCureentSnake() == resPlayer->getCureentSnake());


    player->setCureentSnake(3);

    QVERIFY(db.savePlayer(player) < 0);
    player->setCureentSnake(0);
    player->setName("new");
    QVERIFY(db.savePlayer(player) == id);

    auto tempPlayer = static_cast<decltype (player)>(db.getPlayer(id));

    QVERIFY(tempPlayer->getName() == "new");

    delete tempPlayer;
    delete player;

}

void testSankeServer::testSqlCache() {
    SqlDBCache db;

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


    // TEST PLAYER

    PlayerDBData *player = new PlayerDBData();

    player->setMany(10);
    player->setLastOnline(1000);
    player->setOnlineTime(1001);
    player->setName("test");
    player->setGmail("test@gmail.com");
    player->setCureentSnake(0);
    player->setToken(QCryptographicHash::hash("1", QCryptographicHash::Sha256));

    QVERIFY(db.savePlayer(player) < 0);
    player->setCureentSnake(-1);
    id = db.savePlayer(player);
    QVERIFY(id == 0);

    QVERIFY(!db.getItem(id, 1));
    QVERIFY(db.getItem(id, 0));

    player->setCureentSnake(0);
    QVERIFY(db.savePlayer(player) == id);

    auto resPlayer = static_cast<decltype (player)>(db.getPlayer(id));
    QVERIFY(resPlayer);
    QVERIFY(player->getLastOnline() == resPlayer->getLastOnline());
    QVERIFY(player->getMany() == resPlayer->getMany());
    QVERIFY(player->getOnlineTime() == resPlayer->getOnlineTime());
    QVERIFY(player->getName() == resPlayer->getName());
    QVERIFY(player->getCureentSnake() == resPlayer->getCureentSnake());


    player->setCureentSnake(3);

    QVERIFY(db.savePlayer(player) < 0);
    player->setCureentSnake(0);
    player->setName("new");
    QVERIFY(db.savePlayer(player) == id);

    auto tempPlayer = static_cast<decltype (player)>(db.getPlayer(id));

    QVERIFY(tempPlayer->getName() == "new");


    PlayerDBData *second_player = new PlayerDBData();

    second_player->setMany(10);
    second_player->setLastOnline(1000);
    second_player->setOnlineTime(1001);
    second_player->setName("test2");
    second_player->setGmail("test2@gmail.com");
    second_player->setCureentSnake(-1);
    second_player->setId(-1);
    second_player->setToken(QCryptographicHash::hash("1", QCryptographicHash::Sha256));

    QVERIFY(db.savePlayer(second_player) == 1);

    QVERIFY(db.moveItem(0, 1, 0));

    QSet<int> items;
    QVERIFY(db.getAllItemsOfPalyer(1, items));
    QVERIFY(items.contains(0));
    QVERIFY(items.size() == 1);

    db.updateInterval = 0;

    db.globalUpdateDataBasePrivate(0);

}

void testSankeServer::testSql() {
    testBaseSql();
    testSqlCache();
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
