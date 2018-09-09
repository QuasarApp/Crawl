#include "baseclass.h"

BaseClass::BaseClass() :
    name("BaseClass") {

}

BaseClass::~BaseClass() {

}

QString BaseClass::getName() const {
    return name;
}
