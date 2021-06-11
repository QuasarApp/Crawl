#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QString>

class PluginData;

/**
 * @brief The PluginLoader class This class load shared objects like a plugins.
 */
class PluginLoader {
public:
    PluginLoader();

    /**
     * @brief load This method load a plugin game module.
     * @param pluginPath Path to so or dll plugin file.
     * @return Snake WorldInstance;
     * @note The plugin shiold be implement instance function and if you youse Windows systems marked as a DLL_EXPORT symbol.
     */
    static PluginData load(const QString& pluginPath);
};

#endif // PLUGINLOADER_H
