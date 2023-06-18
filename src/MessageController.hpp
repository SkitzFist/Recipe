#ifndef _SmallView
#define _SmallView

#include "Transmission/EventBus.hpp"
#include "Array.hpp"
#include "MessageView.hpp"
#include "Timer.hpp"

class MessageController : public EventHandler<AddMessageEvent>{
public:
    MessageController(EventBus* eventBus);
    ~MessageController();

    void handleInput();
    void update(float dt);
    void render() const;

    void handleRemoveMessage(int id);

    //////////////////////////////////////////////////////////////////
    ///                    EventHandling                          ///
    virtual void onEvent(const AddMessageEvent& event) override;
    ///////////////////////////////////////////////////////////////

    //debug
    void handleAddMessage(const std::string& title, const std::string& text, const std::string& buttonText);
private:
    struct ViewDeletion{
        int id;
        Timer timer;
        ViewDeletion(int _id, float duration) : id(_id), timer(duration){}
    };

private:
    EventBus* m_eventBus;
    Array<MessageView*> m_messages;
    int m_messageIdCount;

    Array<ViewDeletion> m_deletions;
};

#endif