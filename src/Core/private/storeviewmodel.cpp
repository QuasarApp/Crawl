#include "storeviewmodel.h"
#include "store.h"
#include "user.h"

#include <Crawl/iitem.h>

namespace CRAWL {

StoreViewModel::StoreViewModel() {

}

void StoreViewModel::init(Store *store, User *user) {
    setUser(user);
    setKeys(store->keysList());
    _store = store;
}

void StoreViewModel::buy(int item) {
    if (_store && getUser()) {
        _store->buy(*getUser(), item);
    }
}

const IItem *StoreViewModel::getItem(int id) const {
    if (!_store)
        return nullptr;

    return _store->getItemById(id);
}

}
