#ifndef PLUGINDATA_H
#define PLUGINDATA_H

class IWorld;
class IControl;

/**
 * @brief The PluginData class Private implementation of plugin data.
 * Contains World Implementation and Control implementation.
 */
class PluginData
{
public:
    PluginData();

    IWorld *world() const;
    void setWorld(IWorld *newWorld);

    IControl *control() const;
    void setControl(IControl *newControl);

    /**
     * @brief isValid This method return true if object is valid else false.
     * @return true if object is valid else false.
     */
    bool isValid() const;
private:

    IWorld *_world = nullptr;
    IControl *_control = nullptr;

};

#endif // PLUGINDATA_H
