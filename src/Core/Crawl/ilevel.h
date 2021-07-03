//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef LEVEL_H
#define LEVEL_H

class IWorld;

/**
 * @brief The ILevel class This interface make the world instance object.
 * All levels libraries should be override this interface.
 */
class ILevel
{
public:
    ILevel() = default;
    virtual ~ILevel() = default;

    /**
     * @brief world This method should be return pointer to the level world.
     * @return pointer to the level world.
     */
    virtual IWorld* world() = 0;
};

#endif // LEVEL_H
