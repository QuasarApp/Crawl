#include "baseclass.h"

void BaseClass::setName(const QString &value) {
    name = value;
}

BaseClass::BaseClass() :
    name("BaseClass") {
}

BaseClass::~BaseClass() {

}

QString BaseClass::getName() const {
    return name;
}
