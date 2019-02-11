#ifndef REACTOR_H
#define REACTOR_H
#include <functional>

namespace std {
    class thread;
}

enum class Performance {
    Max,
    Normal,
    Min
};

class Reactor
{
private:
    Performance _per = Performance::Normal;
    std::function<void()> _func;
    bool _pause = false;
    std::thread *_reactor_t = nullptr;
    bool _run;
    bool _finished = false;

public:
    explicit Reactor(std::function<void()> func);
    ~Reactor();
    void setFunction(std::function<void()> func);
    void start();
    void setPause(bool pause);
    void stop();
    Performance performance() const;
    void setPerformance(const Performance &per);
    bool pause() const;
    bool isFinished() const;
    bool isWork() const;
};

#endif // REACTOR_H
