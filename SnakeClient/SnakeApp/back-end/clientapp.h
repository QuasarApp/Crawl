#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include "controller.h"
#include "diff.h"

class QQmlApplicationEngine;

class ClientApp
{
private:
    Controller contr;

public:
    ClientApp();
    ~ClientApp();
    bool init(QQmlApplicationEngine* engine);
};

#endif // CLIENTAPP_H
