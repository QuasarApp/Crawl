#ifndef GUIOBJECTFACTORY_H
#define GUIOBJECTFACTORY_H

#include <QString>

class ItemWorld;

/**
 * @brief The GuiObjectFactory class
 * factory of gui ojects;
 */
class GuiObjectFactory
{
public:
    GuiObjectFactory();

    /**
     * @brief generate - generate the child of GuiObject
     * by object name.
     * @param name - name of class of genereta object
     * @return pointer of generated object.
     * If method called with not valid name then return nullptr.
     */
    static ItemWorld* generate(const QString& name);
};

#endif // GUIOBJECTFACTORY_H
