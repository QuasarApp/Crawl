#include "plugindata.h"
#include "pluginloader.h"
#include <QLibrary>
#include <quasarapp.h>

typedef IWorld* (*worldInstance)();
typedef IControl* (*menuInstance)();


PluginLoader::PluginLoader() {

}

PluginData PluginLoader::load(const QString &pluginPath) {
    PluginData result;
    QLibrary lib(pluginPath);

    if (!lib.load()) {

        QuasarAppUtils::Params::log("Fail to load game module. Message: " + lib.errorString(),
                                    QuasarAppUtils::Error);

        return {};
    }

    worldInstance worldFunc = (worldInstance)lib.resolve("worldInstance");

    if (!worldFunc) {
        QuasarAppUtils::Params::log("Fail to load game module."
                                    " Message: Failed to find a instance function in the %0 module",
                                    QuasarAppUtils::Error);

        lib.unload();
        return {};
    }

    result.setWorld(worldFunc());

    menuInstance menuFunc = (menuInstance)lib.resolve("menuInstance");

    if (!worldFunc) {
        QuasarAppUtils::Params::log("The custom menu not found. Use Default menu implementation.",
                                    QuasarAppUtils::Info);

        return result;
    }

    result.setControl(menuFunc());
    return result;
}
