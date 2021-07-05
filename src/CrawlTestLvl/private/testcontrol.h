#ifndef TESTCONTROL_H
#define TESTCONTROL_H
#include "Crawl/defaultcontrol.h"

/**
 * @brief The TestControl class This controll support custom camera-ratation functions.
 */
class TestControl: public CRAWL::DefaultControl
{
    Q_OBJECT
public:
    TestControl();
    QString initQmlView() const override;

signals:
    void xChanged(double);
    void yChanged(double);
};

#endif // TESTCONTROL_H
