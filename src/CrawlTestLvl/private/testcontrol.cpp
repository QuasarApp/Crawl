//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "testcontrol.h"

namespace TestLvl {

TestControl::TestControl() {

}

QString TestControl::initQmlView() const {
    return "qrc:/qml/TestControl.qml";
}
}
