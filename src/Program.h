#ifndef _Program
#define _Program

#include "State.hpp"

class Program{
public:
    Program();
    ~Program();
    void run();

private:
    State* m_state;
    EventBus* m_eventBus;
    void handleInput();
    void update();
    void render() const;
};

#endif