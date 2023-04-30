#include "EventBus.hpp"

#ifndef _State
#define _State

class State{
public:
    State(EventBus* _eventBus):m_eventBus(_eventBus){}
    virtual ~State(){}
    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void render() const = 0;
protected:
    EventBus* m_eventBus;
};

#endif