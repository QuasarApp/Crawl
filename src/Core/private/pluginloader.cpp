//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "pluginloader.h"
#include <QLibrary>
#include <quasarapp.h>

typedef IWorld* (*worldInstance)();


PluginLoader::PluginLoader() {

}

IWorld* PluginLoader::load(const QString &pluginPath) {
    QLibrary lib(pluginPath);

    if (!lib.load()) {

        QuasarAppUtils::Params::log("Fail to load game module. Message: " + lib.errorString(),
                                    QuasarAppUtils::Error);

        return nullptr;
    }

    worldInstance worldFunc = (worldInstance)lib.resolve("worldInstance");

    if (!worldFunc) {
        QuasarAppUtils::Params::log("Fail to load game module."
                                    " Message: Failed to find a instance function in the %0 module",
                                    QuasarAppUtils::Error);

        lib.unload();
        return nullptr;
    }

    return worldFunc();
}
