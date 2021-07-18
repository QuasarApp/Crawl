//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "autogenerateclaster.h"
namespace CRAWL {

AutoGenerateClaster::AutoGenerateClaster() {
}

void AutoGenerateClaster::generateItems() {

    for (unsigned int count = itemsCount(); count > 0; count--) {
        if (!_factory) {
            QuasarAppUtils::Params::log("Please use the registerItemType method"
                                        " before invoke parent constructor.",
                                        QuasarAppUtils::Error);
            return;
        }

        add(factory());
    }
}

ClasterItem *AutoGenerateClaster::factory() const {

    if (!_factory) {
        QuasarAppUtils::Params::log("Please use the registerBodyitem method"
                                    " before invoke parent constructor.",
                                    QuasarAppUtils::Error);
        return nullptr;
    }

    return _factory();
}
}
