//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef AUTOGENERATECLASTER_H
#define AUTOGENERATECLASTER_H

#include "claster.h"

namespace CRAWL {

/**
 * @brief The AutoGenerateClaster class hs support the registration default claster item class and factory method for the items.
 */
class CRAWL_EXPORT AutoGenerateClaster: public Claster
{
public:
    AutoGenerateClaster();

    /**
     * @brief itemsCount This method sould be return count of the registered items on the claster object.
     * @return items count of the child objects.
     */
    virtual unsigned int itemsCount() const = 0;

    template<class Type>
    /**
     * @brief registerItemType This method register claster item type. Items will be generated in the generateItems method. The size of body companents calc from the itemsCount property.
     */
    void registerItemType() {
        _factory = [](){
            return new Type;
        };
    }

protected:
    /**
     * @brief generateItems This method invoked after iit object on the world and generate list of the default claster items.
     * @note This method should be invked after initialized of this object.
     */
    virtual void generateItems();

    /**
     * @brief factory This method create new item of the claster. See the registerItemType for get more information.
     * @return return new item of the claster item. If the object not registered return nullptr.
     */
    ClasterItem* factory() const;

    /**
     * @brief isClasterItemRegistered
     * @return
     */
    bool isClasterItemRegistered() const;


private:
    std::function<ClasterItem*()> _factory = nullptr;

};

}
#endif // AUTOGENERATECLASTER_H
