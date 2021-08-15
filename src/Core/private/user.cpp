//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "user.h"
namespace CRAWL {

constexpr float tierMul = 1.2;
constexpr int firstTierCount = 10;

/// @private
template <int N>
struct Tiers
{
    enum { value = static_cast<const int>(tierMul * Tiers<N - 1>::value)};
};

/// @private
template <>
struct Tiers<0>
{
    enum { value = 0 };
};

/// @private
template <>
struct Tiers<1>
{
    enum { value = firstTierCount };
};
// End Tiers table

constexpr int maximumTear = 100;

#define T(X) Tiers<X>::value
constexpr int tiersTable[maximumTear] = {T(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9),
                                         T(10), T(11), T(12), T(13), T(14), T(15), T(16), T(17), T(18), T(19),
                                         T(20), T(21), T(22), T(23), T(24), T(25), T(26), T(27), T(28), T(29),
                                         T(30), T(31), T(32), T(33), T(34), T(35), T(36), T(37), T(38), T(39),
                                         T(40), T(41), T(42), T(43), T(44), T(45), T(46), T(47), T(48), T(49),
                                         T(50), T(51), T(52), T(53), T(54), T(55), T(56), T(57), T(58), T(59),
                                         T(60), T(61), T(62), T(63), T(64), T(65), T(66), T(67), T(68), T(69),
                                         T(70), T(71), T(72), T(73), T(74), T(75), T(76), T(77), T(78), T(79),
                                         T(80), T(81), T(82), T(83), T(84), T(85), T(86), T(87), T(88), T(89),
                                         T(90), T(91), T(92), T(93), T(94), T(95), T(96), T(97), T(98), T(99)};
User::User() {

}

const QSet<int> &User::unlockedItems() const {
    return _unlockedItems;
}

bool User::isUnlocked(int item) const {
    return _unlockedItems.contains(item);
}

void User::unclokItem(int item) {
    _unlockedItems.insert(item);
    emit sigUnlcoked(item);
}

void User::droppItem(int item) {
    _unlockedItems.remove(item);
    emit sigDropped(item);
}

void User::setUnlockedItems(const QSet<int> &newUnlockedItems) {
    _unlockedItems = newUnlockedItems;
    emit sigUlockedItemsChanged(newUnlockedItems);
}

int User::recalcTier() {
    int _tier = 0;

    while (getXp() > tiersTable[_tier]) {
        _tier++;
    }

    return _tier;
}

void User::setTier(int tier) {
    if (_tier == tier)
        return;

    _tier = tier;

    emit tierChanged();
}

int User::getXp() const {
    return _xp;
}

void User::setXp(int newXp) {
    if (_xp == newXp)
        return;
    _xp = newXp;

    setTier(recalcTier());

    emit xpChanged();
}

int User::getTier() {
    return _tier;
}

int User::getMoney() const {
    return _money;
}

void User::setMoney(int newMoney) {
    if (_money == newMoney)
        return;
    _money = newMoney;
    emit moneyChanged();
}

}
