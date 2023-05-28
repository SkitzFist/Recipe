#ifndef _EventHandler
#define _EventHandler

#include "Event.hpp"

class EventHandlerID{
public:
    int id;
    EventHandlerID(int _id ) : id(_id){} 
};

inline int idCount;

template <class T>
class EventHandler : public EventHandlerID
{
public:
    EventHandler();
    virtual void onEvent(const T &event) = 0;
    virtual ~EventHandler();
};


template<class T>
EventHandler<T>::EventHandler():EventHandlerID(++idCount){}

template <class T>
EventHandler<T>::~EventHandler() {}

#endif