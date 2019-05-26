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
#include <mainserver.h>

#include "factorynetobjects.h"

// add necessary includes here

#define TEST_LOCAL_SERVER QString(DEFAULT_SERVER) + "Test"
#define TEST_SERVER_ADDRESS  LOCAL_SNAKE_SERVER
#define TEST_SERVER_PORT 27777

class testSankeServer : public QObject
{
    Q_OBJECT

private:
    void testPingServerProtockol(ServerProtocol::Client &cle);
    void testStateServerProtockol(ServerProtocol::Client &cle);
    void testBanServerProtockol(ServerProtocol::Client& cle);
    void testUnBanServerProtockol(ServerProtocol::Client& cle);
    void testRestartServerProtockol(ServerProtocol::Client& cle);
    void testStopServerProtockol(ServerProtocol::Client& cle);

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

testSankeServer::testSankeServer() {

}

testSankeServer::~testSankeServer() {

}

void testSankeServer::initTestCase() {
    ClientProtocol::initClientProtockol();
}

void testSankeServer::cleanupTestCase() {

}

void testSankeServer::testPingServerProtockol(ServerProtocol::Client &cle) {
    QuasarAppUtils::Params::setEnable("verbose", true);


    bool isWork = false;
    QMetaObject::Connection m_connection;

    m_connection = QObject::connect(&cle, &ServerProtocol::Client::sigIncommingData,
                     [&isWork, &m_connection] (const QVariantMap& map) {

        isWork = map["res"].toString() == "Pong";
        disconnect(m_connection);

    });

    QVERIFY(cle.ping());

    QVERIFY(cle.wait(1000));

    QVERIFY(isWork);

}

void testSankeServer::testStateServerProtockol(ServerProtocol::Client& cle) {

    bool isWork = false;
    QMetaObject::Connection m_connection;

    m_connection = QObject::connect(&cle, &ServerProtocol::Client::sigIncommingData,
                     [&isWork, &m_connection] (const QVariantMap& map) {

        isWork = !map.contains("Error");
        disconnect(m_connection);

    });


    QVERIFY(cle.getState());
    QVERIFY(cle.wait(1000));
    QVERIFY(isWork);


}

void testSankeServer::testBanServerProtockol(ServerProtocol::Client& cle) {

    bool isWork = false;

    QMetaObject::Connection m_connection;

    m_connection = QObject::connect(&cle, &ServerProtocol::Client::sigIncommingData,
                     [&isWork, &m_connection] (const QVariantMap& map) {

        isWork = !map.contains("Error");
        disconnect(m_connection);
    });

    QVERIFY(!cle.ban(QHostAddress()));

    QVERIFY(cle.ban(QHostAddress("192.192.192.192")));
    QVERIFY(cle.wait(1000));

    QVERIFY(isWork);

}

void testSankeServer::testUnBanServerProtockol(ServerProtocol::Client& cle)
{

    bool isWork = false;
    QMetaObject::Connection m_connection;

    m_connection = QObject::connect(&cle, &ServerProtocol::Client::sigIncommingData,
                     [&isWork, &m_connection] (const QVariantMap& map) {

        isWork = !map.contains("Error");
        disconnect(m_connection);

    });

    QVERIFY(!cle.unBan(QHostAddress()));

    QVERIFY(cle.unBan(QHostAddress("192.192.192.192")));
    QVERIFY(cle.wait(1000));

    QVERIFY(isWork);

}

void testSankeServer::testRestartServerProtockol(ServerProtocol::Client& cle) {

    bool isWork = false;
    QMetaObject::Connection m_connection;

    m_connection = QObject::connect(&cle, &ServerProtocol::Client::sigIncommingData,
                     [&isWork, &m_connection] (const QVariantMap& map) {

        if (isWork) {
            isWork = map.value("Address") == QString("%0:%1").arg(TEST_SERVER_ADDRESS).arg(TEST_SERVER_PORT);
            isWork =  !map.contains("Error");
            disconnect(m_connection);

        } else {
            isWork =  !map.contains("Error");
        }

    });

    QVERIFY(!cle.unBan(QHostAddress()));

    QVERIFY(cle.unBan(QHostAddress("192.192.192.192")));
    QVERIFY(cle.wait(1000));

    QVERIFY(isWork);

    QVERIFY(!cle.restart("lolo", 0));

    QVERIFY(!cle.restart("192.168.1.999", 0));
    QVERIFY(!cle.restart("192.168.1.99", 0));
    QVERIFY(!cle.restart("192.168.1.9", 0));

    QVERIFY(!cle.restart("-1.168.1.999", 77));
    QVERIFY(!cle.restart("192.168.-1.99", 7777));

    QVERIFY(cle.restart("127.168.1.9", 3456));

    cle.wait(1000);

    QVERIFY(cle.restart(TEST_SERVER_ADDRESS, TEST_SERVER_PORT));

    cle.wait(1000);
    QVERIFY(isWork);

}

void testSankeServer::testStopServerProtockol(ServerProtocol::Client& cle) {

    bool isWork = false;
    QMetaObject::Connection m_connection;

    m_connection = QObject::connect(&cle, &ServerProtocol::Client::sigIncommingData,
                     [&isWork, &m_connection] (const QVariantMap& map) {

        isWork = !map.contains("Error");
        disconnect(m_connection);

    });

    QVERIFY(cle.stop());

    cle.wait(1000);

    QVERIFY(isWork);
}

void testSankeServer::testPingClientProtockol() {

    QuasarAppUtils::Params::setEnable("verbose", true);

    int argc = 0;
    char * argv[] = {nullptr};

    QCoreApplication app(argc, argv);

    auto serv = new ClientProtocol::Server(this);

    QVERIFY(serv->run(TEST_SERVER_ADDRESS, TEST_SERVER_PORT));

    auto client = new ClientProtocol::Client(TEST_SERVER_ADDRESS,
                                             TEST_SERVER_PORT,
                                             this);

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
    ClientProtocol::Client cle(TEST_SERVER_ADDRESS, TEST_SERVER_PORT);

    auto pass = QCryptographicHash::hash("testpass", QCryptographicHash::Sha512);
    QVERIFY(!cle.login("Test@gmail.com", pass));

    pass = QCryptographicHash::hash("testpass", QCryptographicHash::Sha256);
    QVERIFY(cle.login("Test@gmail.com", pass));

}

void testSankeServer::testUserData() {
    ClientProtocol::Client cle(TEST_SERVER_ADDRESS, TEST_SERVER_PORT);

    QVERIFY(!cle.updateData());

    auto token = QCryptographicHash::hash("testtoken", QCryptographicHash::Sha256);
    cle._token = token;
    cle._online = true;

    QVERIFY(cle.updateData());
}

void testSankeServer::testGetItem() {

    ClientProtocol::Client cle(TEST_SERVER_ADDRESS, TEST_SERVER_PORT);

    QVERIFY(!cle.updateData());

    auto token = QCryptographicHash::hash("testtoken", QCryptographicHash::Sha256);
    cle._token = token;
    cle._online = true;

    QVERIFY(cle.getItem(1));
}

void testSankeServer::testApplyData() {

    ClientProtocol::Client cle(TEST_SERVER_ADDRESS, TEST_SERVER_PORT);


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

    bool init = db.initDb("./test.db");

    if (!init) {
        QFile::remove("./test.db");
    }

    QVERIFY(init);

    ClientProtocol::Snake snake;
    snake.setSpeed(10);
    snake.setSkillet(QList<float>() << 1);
    snake.setSnakeClass(0);


    // TEST ITEM

    ClientProtocol::Snake resSnake;

    QVERIFY(db.saveItem(&snake) < 0);
    snake.setId(0);
    int id = db.saveItem(&snake);

    QVERIFY(id == 0);

    QVERIFY(db.getItem(id).parse(resSnake));

    QVERIFY(snake.getSpeed() == resSnake.getSpeed());
    QVERIFY(snake.getSkillet() == resSnake.getSkillet());
    QVERIFY(snake.getSnakeClass() == resSnake.getSnakeClass());
    QVERIFY(snake.getClass() == resSnake.getClass());
    QVERIFY(snake.id() == resSnake.id());

    resSnake.setSnakeClass(10);
    QVERIFY(id == db.saveItem(Item(&resSnake)));

    ClientProtocol::Snake temp;
    QVERIFY(db.getItem(id).parse(temp));

    QVERIFY(temp.getSnakeClass() == 10);


    // TEST PLAYER

    PlayerDBData player = PlayerDBData();

    player.setMany(10);
    player.setLastOnline(1000);
    player.setOnlineTime(1001);
    player.setName("test");
    player.setGmail("test@gmail.com");
    player.setCureentSnake(0);

    QVERIFY(db.savePlayer(player) < 0);
    player.setId(0);

    QVERIFY(db.savePlayer(player) < 0);
    player.setCureentSnake(-1);
    id = db.savePlayer(player);
    QVERIFY(id == 0);

    QVERIFY(!db.saveowners(id, QSet<int>() << 1));
    QVERIFY(db.saveowners(id, QSet<int>() << 0));

    QSet<int> items;
    QVERIFY(db.getAllItemsOfPalyer(id, items));
    QVERIFY(items.contains(0));
    QVERIFY(items.size() == 1);


    player.setCureentSnake(0);
    id = db.savePlayer(player);

    auto resPlayer = db.getPlayer(id);
    QVERIFY(resPlayer.isValid());
    QVERIFY(player.getLastOnline() == resPlayer.getLastOnline());
    QVERIFY(player.getMany() == resPlayer.getMany());
    QVERIFY(player.getOnlineTime() == resPlayer.getOnlineTime());
    QVERIFY(player.getName() == resPlayer.getName());
    QVERIFY(player.getCureentSnake() == resPlayer.getCureentSnake());


    player.setCureentSnake(3);

    QVERIFY(db.savePlayer(player) < 0);
    player.setCureentSnake(0);
    player.setName("new");
    QVERIFY(db.savePlayer(player) == id);

    resPlayer = db.getPlayer(id);

    QVERIFY(resPlayer.getName() == "new");

}

void testSankeServer::testSqlCache() {
    SqlDBCache db;

    QFile::remove("./test2.db");

    bool init = db.initDb("./test2.db");

    if (!init) {
        QFile::remove("./test2.db");
    }

    QVERIFY(init);


    ClientProtocol::Snake snake;
    snake.setSpeed(10);
    snake.setSkillet(QList<float>() << 1);
    snake.setSnakeClass(0);


    // TEST ITEM

    ClientProtocol::Snake resSnake;

    int id = db.saveItem(&snake);

    QVERIFY(id == 0);
    snake.setId(id);

    QVERIFY(db.getItem(id).parse(resSnake));

    QVERIFY(snake.getSpeed() == resSnake.getSpeed());
    QVERIFY(snake.getSkillet() == resSnake.getSkillet());
    QVERIFY(snake.getSnakeClass() == resSnake.getSnakeClass());
    QVERIFY(snake.getClass() == resSnake.getClass());
    QVERIFY(snake.id() == resSnake.id());

    resSnake.setSnakeClass(10);
    QVERIFY(id == db.saveItem(Item(&resSnake)));

    ClientProtocol::Snake temp;
    QVERIFY(db.getItem(id).parse(temp));

    QVERIFY(temp.getSnakeClass() == 10);


    // TEST PLAYER

    PlayerDBData player = PlayerDBData();

    player.setMany(10);
    player.setLastOnline(1000);
    player.setOnlineTime(1001);
    player.setName("test");
    player.setGmail("test@gmail.com");
    player.setCureentSnake(0);

    QVERIFY(db.savePlayer(player) < 0);
    player.setId(0);

    QVERIFY(db.savePlayer(player) < 0);
    player.setCureentSnake(-1);
    id = db.savePlayer(player);
    QVERIFY(id == 0);

    QVERIFY(!db.getItem(id, 1));
    QVERIFY(db.getItem(id, 0));

    player.setCureentSnake(0);
    QVERIFY(db.savePlayer(player) == id);

    auto resPlayer = db.getPlayer(id);
    QVERIFY(resPlayer.isValid());
    QVERIFY(player.getLastOnline() == resPlayer.getLastOnline());
    QVERIFY(player.getMany() == resPlayer.getMany());
    QVERIFY(player.getOnlineTime() == resPlayer.getOnlineTime());
    QVERIFY(player.getName() == resPlayer.getName());
    QVERIFY(player.getCureentSnake() == resPlayer.getCureentSnake());


    player.setCureentSnake(3);

    QVERIFY(db.savePlayer(player) < 0);
    player.setCureentSnake(0);
    player.setName("new");
    QVERIFY(db.savePlayer(player) == id);

    resPlayer = db.getPlayer(id);

    QVERIFY(resPlayer.getName() == "new");


    PlayerDBData second_player = PlayerDBData();

    second_player.setMany(10);
    second_player.setLastOnline(1000);
    second_player.setOnlineTime(1001);
    second_player.setName("test2");
    second_player.setGmail("test2@gmail.com");
    second_player.setCureentSnake(-1);
    second_player.setId(-1);

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

    int argc =0;
    char * argv[] = {nullptr};

    QCoreApplication app(argc, argv);

    auto serv = new MainServer(this);
    QVERIFY(serv->run("", 0 , "", TEST_LOCAL_SERVER, true));
    ServerProtocol::Client cle(TEST_LOCAL_SERVER);

    QTimer::singleShot(0, [this, &app, &cle]() {
        testPingServerProtockol(cle);
        testStateServerProtockol(cle);
        testBanServerProtockol(cle);
        testUnBanServerProtockol(cle);
        testRestartServerProtockol(cle);
        testStopServerProtockol(cle);
        app.exit(0);
    });

    app.exec();

}

void testSankeServer::testClientProtockol() {
    testPingClientProtockol();

    auto serv = new ClientProtocol::Server(this);
    QVERIFY(serv->run(TEST_SERVER_ADDRESS, TEST_SERVER_PORT));

    testLogin();
    testGetItem();
    testUserData();
    testApplyData();
}

QTEST_APPLESS_MAIN(testSankeServer)

#include "tst_testsnakeserver.moc"
