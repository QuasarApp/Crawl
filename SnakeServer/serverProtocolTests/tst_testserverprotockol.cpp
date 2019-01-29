#include <QtTest>

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

}

QTEST_APPLESS_MAIN(testServerProtocol)

#include "tst_testserverprotockol.moc"
