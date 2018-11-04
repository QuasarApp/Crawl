#include "diff.h"

QList<int> Diff::getRemoveIds() const {
    return removeIds;
}

void Diff::setRemoveIds(const QList<int> &value) {
    removeIds = value;
}

QList<int> Diff::getAddedIds() const {
    return addedIds;
}

void Diff::setAddedIds(const QList<int> &value) {
    addedIds = value;
}

Diff::Diff(){

}
