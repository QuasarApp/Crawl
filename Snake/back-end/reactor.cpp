#include "reactor.h"
#include <thread>

bool Reactor::pause() const {
    return _pause;
}

bool Reactor::isFinished() const {
    return _finished;
}

bool Reactor::isWork() const {
    return _reactor_t && !_finished;
}

Reactor::Reactor(std::function<void ()> func) {
    setFunction(func);
}

Reactor::~Reactor() {
    stop();
}

void Reactor::setFunction(std::function<void ()> func) {

    if (isWork()) {
        stop();
    }

    _func = [this, func]() {

        while (_run) {
            if (_per != Performance::Max) {
                switch (_per) {

                case Performance::Normal: {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    break;
                }

                case Performance::Min: {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    break;
                }

                default:
                    break;
                }
            }

            if (_pause)
                return;

            func();
        }

        _finished = true;
    };


}

void Reactor::start() {
    _run = true;
    _finished = false;

    _reactor_t = new std::thread(_func);
    _reactor_t->detach();
}

void Reactor::setPause(bool pause) {
    _pause = pause;
}

void Reactor::stop() {
    _run = false;

    while (!_finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    delete _reactor_t;
    _reactor_t = nullptr;
}

Performance Reactor::performance() const {
    return _per;
}

void Reactor::setPerformance(const Performance &per) {
    _per = per;
}
