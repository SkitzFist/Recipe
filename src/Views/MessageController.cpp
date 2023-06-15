#include "MessageController.hpp"
#include "Settings.h"

MessageController::MessageController(EventBus* eventBus):
    m_eventBus(eventBus), m_messages(3), m_messageIdCount(0){

    m_eventBus->registerHandler<AddMessageEvent>(this);
}

MessageController::~MessageController(){
    for(int i = 0; i < m_messages.size(); ++i){
        delete m_messages[i];
    }

    for(int i = 0; i < m_messages.size(); ++i){
        delete m_messages[i];
    }
}

void MessageController::handleInput(){
     for(MessageView* view : m_messages){
        view->handleInput();
     }
}

void MessageController::update(float dt){
    for(MessageView* view : m_messages){
        view->update(dt);
    }

    for(int i = 0; i < m_deletions.size(); ++i){
        if(m_deletions[i].timer.hasElapsed()){
            int messagesIndex = m_deletions[i].id;
            
            MessageView* view = m_messages[messagesIndex];
            delete view;

            m_messages.remove(messagesIndex);
            m_deletions.remove(i);
            --i;
        }
    }
}

void MessageController::render() const{
    for(MessageView* view : m_messages){
        view->render();
    }
}

void MessageController::handleAddMessage(const std::string& title, const std::string& text, const std::string& buttonText){
    MessageView* message = new MessageView(++m_messageIdCount, title, text, buttonText);
    MessageController* ptr = this;
    message->onClick.connect([ptr](int id){
        ptr->handleRemoveMessage(id);
    });

    m_messages.add(message);
}

void MessageController::handleRemoveMessage(int id){
    for(int i = 0; i < m_messages.size(); ++i){
        if(m_messages[i]->getId() == id){
            m_deletions.add(ViewDeletion(i, Settings::VIEW_TRANSITION_DURATION_MS + 100.f));
        }
    }
}

//////////////
// Events ///
void MessageController::onEvent(const AddMessageEvent& event){
    Log::info("onEvent");
    handleAddMessage(event.title, event.text, event.buttonText);
}