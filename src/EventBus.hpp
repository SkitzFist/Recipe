#ifndef _EventBus
#define _EventBus

#include <unordered_map>
#include <vector>
#include <typeindex>

#include "EventHandler.hpp"

class EventBus{
public:
    EventBus(){

    }

    ~EventBus(){

    }

    template <class EventType>
    void registerHandler(EventHandler<EventType>* handler){
        m_handlers[typeid(EventType)].emplace_back((ID*)handler);
    }

    template <class EventType>
    void fireEvent(const EventType& event){
        if(!eventTypeExists(typeid(EventType))){
            return;
        }

        std::vector<ID*>* vec = &m_handlers[typeid(EventType)];
        
        for(std::size_t i = 0; i < vec->size(); ++i){
            ID* handlerID = vec->at(i);
            EventHandler<EventType>* handler = (EventHandler<EventType>*)handlerID;
            handler->onEvent(event);
        }
    }

    template <class EventType>
    void removeHandler(EventHandler<EventType>* handler){
        std::vector<ID*>* vec = &m_handlers[typeid(EventType)];
        if(!vec){
            return;
        }

        for(std::size_t i = 0; i < vec->size(); ++i){
            if(vec->at(i)->id == handler->id){
                vec->erase(vec->begin() + i);
                break;
            }
        }
    }

private:

    bool eventTypeExists(std::type_index typeIndex){
         auto it = m_handlers.find(typeIndex);
         return it != m_handlers.end();
    }

    std::unordered_map<std::type_index, std::vector<ID*>> m_handlers;
};

#endif
