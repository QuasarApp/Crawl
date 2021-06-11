#include "plugindata.h"

PluginData::PluginData() {

}

IWorld *PluginData::world() const {
    return _world;
}

void PluginData::setWorld(IWorld *newWorld) {
    _world = newWorld;
}

IControl *PluginData::control() const {
    return _control;
}

void PluginData::setControl(IControl *newControl) {
    _control = newControl;
}

bool PluginData::isValid() const {
    return _world;
}
