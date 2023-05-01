#ifndef _Program
#define _Program

#include "StateSwitcher.hpp"

class Program{
public:
    Program(EventBus* eventBus);
    ~Program();
    void run();

private:
    StateSwitcher* m_stateSwitcher;
    void handleInput(State* state);
    void update(State* state);
    void render(State* state) const;
};

#endif