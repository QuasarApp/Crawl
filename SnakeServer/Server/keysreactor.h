#ifndef KEYSREACTOR_H
#define KEYSREACTOR_H

#include <qrsaencryption.h>
#include <QtConcurrent>
#include <rsakeyspool.h>

#define DEFAULT_KEYPOOL_SIZE 10

class KeysReactor: public QObject
{
    Q_OBJECT
private:
    ClientProtocol::RSAKeysPool _pool;
    QRSAEncryption _generator;
    int _poolSize = DEFAULT_KEYPOOL_SIZE;
    QHash<QRSAEncryption::Rsa, bool> _mutexs;
    void generateKeys(QRSAEncryption::Rsa);

private slots:
    void handleGenerateNewKeys();

public:
    KeysReactor(bool ForceGenerateKey, QObject *ptr = nullptr);

    ~KeysReactor() override;

    ClientProtocol::RSAKeysPool* getPool();
    int getPoolSize() const;
    void setPoolSize(int value);

};

#endif // KEYSREACTOR_H
