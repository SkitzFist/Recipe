#ifndef _Program
#define _Program

#include "EventBus.hpp"
#include "View.h"

class Program{
public:
    Program(EventBus* eventBus);
    ~Program();
    void run();

private:
    Timer m_frameTimer;

    void handleInput();
    void update(float dt);
    void render() const;

    View* m_view;
        
};

#endif