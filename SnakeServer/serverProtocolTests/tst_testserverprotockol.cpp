#include <QtTest>
#include <server.h>
#include <client.h>
#include <thread>
#include <quasarapp.h>
#include <QCoreApplication>

// add necessary includes here

class testServerProtocol : public QObject
{
    Q_OBJECT

public:
    testServerProtocol();
    ~testServerProtocol();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testPing();

};

testServerProtocol::testServerProtocol()
{

}

testServerProtocol::~testServerProtocol()
{

}

void testServerProtocol::initTestCase()
{

}

void testServerProtocol::cleanupTestCase()
{

}

void testServerProtocol::testPing()
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

    app.exec();

    QVERIFY(isWork);

    delete serv;
    delete client;

}

QTEST_APPLESS_MAIN(testServerProtocol)

#include "tst_testserverprotockol.moc"
