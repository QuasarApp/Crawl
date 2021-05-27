#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include "controller.h"
#include "diff.h"

inline void initSnakeProjectResources() { Q_INIT_RESOURCE(SnakeProject); }

class QQmlApplicationEngine;

class SNAKEPROJECT_EXPORT ClientApp
{
private:
    Controller contr;

    QByteArray initTheme();

    void initLang();
    
public:
    ClientApp();
    ~ClientApp();
    bool init(QQmlApplicationEngine* engine);
};

#endif // CLIENTAPP_H
