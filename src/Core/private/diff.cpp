#include "diff.h"

const QList<int>& Diff::getRemoveIds() const {
    return removeIds;
}

void Diff::setRemoveIds(const QList<int> &value) {
    removeIds = value;
}

const QList<GuiObject*>& Diff::getAddedIds() const {
    return addedIds;
}

void Diff::setAddedIds(const QList<GuiObject *> &value) {
    addedIds = value;
}

Diff::Diff(){

}
