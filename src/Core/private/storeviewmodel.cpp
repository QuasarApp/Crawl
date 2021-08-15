#include "storeviewmodel.h"
#include "store.h"
#include "user.h"

#include <Crawl/iitem.h>

namespace CRAWL {

StoreViewModel::StoreViewModel() {

}

void StoreViewModel::init(Store *store, User *user) {
    setUser(user);
    setStore(store);
    setKeys(store->keysList());
}

void StoreViewModel::buy(int item) {
    if (store() && getUser()) {
        store()->buy(*getUser(), item);
    }
}

const IItem *StoreViewModel::getItem(int id) const {
    if (!store())
        return nullptr;

    return store()->getItemById(id);
}

}
