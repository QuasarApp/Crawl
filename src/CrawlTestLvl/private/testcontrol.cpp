#include "testcontrol.h"
namespace TestLvl {

TestControl::TestControl() {

}

QString TestControl::initQmlView() const {
    return "qrc:/qml/TestControl.qml";
}
}
