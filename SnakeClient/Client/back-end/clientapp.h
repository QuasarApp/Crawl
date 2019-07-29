#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include "controller.h"
#include "diff.h"
#include "client_global.h"

class QQmlApplicationEngine;

class CLIENTSHARED_EXPORT ClientApp
{
private:
    Controller contr;

public:
    ClientApp();
    bool init(QQmlApplicationEngine* engine);
};

#endif // CLIENTAPP_H
