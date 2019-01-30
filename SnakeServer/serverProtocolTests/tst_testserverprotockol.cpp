#include <QtTest>
#include <server.h>
#include <client.h>
#include <thread>
#include <quasarapp.h>

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
    char * array[] = {
        "verbose"
    };

    QuasarAppUtils::Params::parseParams(1, array);

    auto serv = new ServerProtocol::Server(this);
    QVERIFY(serv->run(DEFAULT_SERVER));

    auto client = new ServerProtocol::Client(this);
    ServerProtocol::Client cli;

    bool isWork = false;
    QObject::connect(client, &ServerProtocol::Client::sigIncommingData,
                     [&isWork] (const QVariantMap& map) {

        isWork = map["res"].toString() == "Pong";

    });

    ServerProtocol::Package pkg;
    pkg.hdr.command = ServerProtocol::ping;

    QVERIFY(cli.sendPackage(pkg));

    auto current = QDateTime::currentMSecsSinceEpoch();
    while(!isWork || QDateTime::currentMSecsSinceEpoch() - current > 10000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    QVERIFY(isWork);

    delete serv;
    delete client;

}

QTEST_APPLESS_MAIN(testServerProtocol)

#include "tst_testserverprotockol.moc"
