#ifndef _EventHandler
#define _EventHandler

#include "ID.hpp"
#include "Event.hpp"

template <class T>
class EventHandler : public ID
{
public:
    EventHandler(int id);
    virtual void onEvent(const T &event) = 0;
    virtual ~EventHandler();
};

template <class T>
EventHandler<T>::EventHandler(int _id) : ID(_id) {}

template <class T>
EventHandler<T>::~EventHandler() {}

#endif