#include "iplayer.h"

IPlayer::IPlayer() {

}

GameResult IPlayer::getCurrentStatus() const {
    return {_currentPoints, static_cast<int>(position().distanceToPoint({0,0,0}))};
}

bool IPlayer::isDead() const {
    return _fDead;
}

void IPlayer::reward(int value) {
    _currentPoints += value;
}

void IPlayer::fine(int value) {
    _currentPoints -= value;
}

void IPlayer::kill() {
    _fDead = true;
}
