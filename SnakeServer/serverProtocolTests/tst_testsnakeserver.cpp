#include <QtTest>
#include <cp.h>
#include <sp.h>
#include <thread>
#include <quasarapp.h>
#include <QCoreApplication>
#include <streamers.h>
#include <QCryptographicHash>
#include <sqldbwriter.h>

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
                     [&isWork, &app] (const QVariantMap& map) {

        isWork = map["command"].toInt() == ClientProtocol::NetworkClasses::Ping;
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

    auto pass = QCryptographicHash::hash("testpass", QCryptographicHash::Sha256);
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

    QVariantMap tempItem;

    QVERIFY(ClientProtocol::FactoryNetObjects::build(
                ClientProtocol::NetworkClasses::Snake, tempItem));

    QVERIFY(ClientProtocol::FactoryNetObjects::fillRandomData(tempItem));

    QVariantMap resItem;

    QVERIFY(db.saveItem(tempItem) < 0);
    tempItem["id"] = 0;
    int id = db.saveItem(tempItem);

    QVERIFY(id == 0);
    QVERIFY(db.getItem(id, resItem));
    QVERIFY(tempItem.size() == resItem.size());

    for (auto &key :tempItem.keys()) {
        QVERIFY(tempItem.value(key).toString() == resItem.value(key).toString());
    }

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
