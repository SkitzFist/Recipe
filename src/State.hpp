#include "EventBus.hpp"

#ifndef _State
#define _State


class State{
public:
    State(const EventBus& _eventBus):m_eventBus(_eventBus){}
    virtual ~State(){}
    virtual State* handleInput() = 0;
    virtual State* update(float dt) = 0;
    virtual void render() const = 0;
protected:
    EventBus m_eventBus;
};

#endif