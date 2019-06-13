#include "keysreactor.h"

ClientProtocol::RSAKeysPool *KeysReactor::getPool() {
    return &_pool;
}

int KeysReactor::getPoolSize() const {
    return _poolSize;
}

void KeysReactor::setPoolSize(int value) {
    if (_poolSize != value) {
        _poolSize = value;
        handleGenerateNewKeys();
    }
}

void KeysReactor::generateKeys(QRSAEncryption::Rsa rsa) {
    QByteArray pub, priv;

    if (_poolSize > _pool.size(rsa)) {
        _generator.generatePairKey(pub, priv, rsa);
        _pool.addNewKey(rsa, {pub, priv});
    }

    return;
}

void KeysReactor::handleGenerateNewKeys() {

    auto generatorFunc = [this] (QRSAEncryption::Rsa rsa) {

        if (_mutexs[rsa]) {
            return;
        }

        _mutexs[rsa] = true;

        QByteArray pub, priv;

        while (_poolSize > _pool.size(rsa)) {
            _generator.generatePairKey(pub, priv, rsa);
            _pool.addNewKey(rsa, {pub, priv});
        }

        _mutexs[rsa] = false;

        return;
    };

    QtConcurrent::run(generatorFunc, QRSAEncryption::RSA_64);
    QtConcurrent::run(generatorFunc, QRSAEncryption::RSA_128);

}

KeysReactor::KeysReactor(bool ForceGenerateKey, QObject *ptr):
    QObject (ptr) {

    _mutexs[QRSAEncryption::RSA_64] = false;
    _mutexs[QRSAEncryption::RSA_128] = false;

    if (ForceGenerateKey) {
        generateKeys(QRSAEncryption::RSA_64);
        generateKeys(QRSAEncryption::RSA_128);

    }

    handleGenerateNewKeys();

    connect(&_pool, &ClientProtocol::RSAKeysPool::sigKeyTaked,
            this, &KeysReactor::handleGenerateNewKeys);
}

KeysReactor::~KeysReactor() {

}
