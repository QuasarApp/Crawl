#ifndef DEFAULTBACKGROUNDAI_H
#define DEFAULTBACKGROUNDAI_H

#include "Crawl/defaultcontrol.h"
#include <Crawl/iai.h>

class QTimer;

class DefaultBackgroundAI: public DefaultControl, public IAI {
    Q_OBJECT
public:
    DefaultBackgroundAI();
    ~DefaultBackgroundAI();

    // IAI interface
public:
    void startAI() override;
    void stopAI() override;

private slots:
    void handleTimerTriger();

private:
    QTimer *_timer = nullptr;
};

#endif // DEFAULTBACKGROUNDAI_H
