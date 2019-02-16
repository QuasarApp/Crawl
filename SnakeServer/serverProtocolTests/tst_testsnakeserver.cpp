#include <QtTest>
#include <cp.h>
#include <sp.h>
#include <thread>
#include <quasarapp.h>
#include <QCoreApplication>

// add necessary includes here

class testSankeServer : public QObject
{
    Q_OBJECT

private:
    void testPingServerProtockol();

    void testPingClientProtockol();
    void testLoginClientProtockol();
    void testUserDataClientProtockol();
    void testGetItemClientProtockol();

public:
    testSankeServer();


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

    ServerProtocol::Package pkg;
    pkg.hdr.command = ServerProtocol::ping;

    QVERIFY(client->sendPackage(pkg));

    QTimer::singleShot(1000, [&app](){
        app.exit(0);
    });

    app.exec();

    QVERIFY(isWork);

    delete serv;
    delete client;

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

        isWork = map["res"].toString() == "Pong";
        app.exit(0);

    });

    ClientProtocol::Package pkg;
    pkg.hdr.command = ClientProtocol::Ping;

    QVERIFY(client->sendPackage(pkg));

    QTimer::singleShot(1000, [&app](){
        app.exit(0);
    });

    app.exec();

    QVERIFY(isWork);

    delete serv;
    delete client;
}

void testSankeServer::testLoginClientProtockol() {

}

void testSankeServer::testUserDataClientProtockol() {

}

void testSankeServer::testGetItemClientProtockol() {

}

void testSankeServer::testServerProtockol() {
    testPingServerProtockol();
}

void testSankeServer::testClientProtockol() {
    testPingClientProtockol();

    testLoginClientProtockol();
    testGetItemClientProtockol();
    testUserDataClientProtockol();
}

QTEST_APPLESS_MAIN(testSankeServer)

#include "tst_testsnakeserver.moc"
