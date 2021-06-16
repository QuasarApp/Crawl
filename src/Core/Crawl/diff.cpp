#include "diff.h"

QList<int> Diff::getAddedIds() const {
    return addedIds;
}

QList<int> Diff::getRemoveIds() const {
    return removeIds;
}

