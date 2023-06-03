#ifndef _AddRecipeView
#define _AddRecipeView

#include <vector>
#include <memory>

#include "View.h"

#include "Settings.h"
#include "Transmission/EventBus.hpp"
#include "Ui/Button.hpp"
#include "TabCycling.h"
#include "Texts.hpp"

template <class EventType>
class BigView : public View{
public:
    BigView(const Vector2 &outOfViewPos, const Vector2 &inViewPos, EventBus *eventBus, 
        const std::string &title, const std::string &buttonText);
    virtual ~BigView();

    virtual void handleInput() override;
    virtual void update(const float dt) override;
    virtual void render() const override;

    void sendEvent();
private:
    EventBus* m_eventBus;
    
    Array<InputGroup*> m_inputGroups;
    TabCycling m_tabCycling;
    UiButton* m_button;
    std::string m_title;

    bool allInputFieldHasValidInput();
};

///////// IMPL \\\\\\\\\\/\/

template <class EventType>
BigView<EventType>::BigView(const Vector2 &outOfViewPos, const Vector2 &inViewPos, EventBus *eventBus,
    const std::string& title, const std::string& buttonText) : 
    View(outOfViewPos, inViewPos, Settings::BIG_VIEW_SIZE), m_eventBus(eventBus), m_inputGroups(3),
    m_title(title)
{
    Vector2 inputFieldSize = {
        Settings::BIG_VIEW_SIZE.x * 0.9f,
        Settings::BIG_VIEW_SIZE.y * 0.05
    };

    m_localXAlignment = (Settings::BIG_VIEW_SIZE.x / 2.f) - (inputFieldSize.x / 2.f);

    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Name"
    ));

    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Reference"
    ));

    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Tags"
    ));

    BigView *ptr = this;
    for (InputGroup *group : m_inputGroups){
        group->inputField->onSubmit.connect([ptr](){ 
            ptr->sendEvent(); 
        });
        m_tabCycling.addInputField(group->inputField);
    }

    m_button = new Button(m_currentPos, Vector2{inputFieldSize.x / 2.f, 50}, buttonText);
    m_button->onClick.connect([this](){
        this->sendEvent(); 
    });
}

template <class EventType>
BigView<EventType>::~BigView()
{
    m_inputGroups.clear();
    delete m_button;
}

template <class EventType>
void BigView<EventType>::handleInput()
{

    if (!isVisible()){
        return;
    }

    m_tabCycling.handleInput();

    for (InputGroup *group : m_inputGroups){
        group->inputField->handleInput();
    }

    m_button->handleInput();
}

template <class EventType>
void BigView<EventType>::update(const float dt)
{
    View::update(dt);

    for (InputGroup *group : m_inputGroups){
        group->inputField->update(dt);
    }
}

template <class EventType>
void BigView<EventType>::render() const
{
    BeginBlendMode(BLEND_ADDITIVE);
    DrawRectangle(m_currentPos.x, m_currentPos.y, Settings::BIG_VIEW_SIZE.x,
                  Settings::BIG_VIEW_SIZE.y, Settings::VIEW_BGR_COLOR);
    EndBlendMode();

    int titleFontSize = GetFontDefault().baseSize * 5;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), m_title.c_str(), titleFontSize, 2.f);
    Vector2 titlePos = {
        m_currentPos.x + (m_size.x / 2.f) - (textSize.x / 2.f),
        m_currentPos.y + (m_size.y * 0.05f)
    };
    DrawText(m_title.c_str(), titlePos.x, titlePos.y, titleFontSize, Settings::BUTTON_TEXT_COLOR);

    float nextYPos = m_size.y * 0.3f;
    for (const InputGroup *group : m_inputGroups){
        float fontSize = GetFontDefault().baseSize * 4.f;
        DrawTextEx(GetFontDefault(), group->title.c_str(), {m_currentPos.x + m_localXAlignment, nextYPos}, fontSize, 2.f, Settings::BUTTON_TEXT_COLOR);
        Vector2 textSize = MeasureTextEx(GetFontDefault(), group->title.c_str(), fontSize, 2.f);
        nextYPos += textSize.y * 1.2f;
        group->inputField->setPos({m_currentPos.x + m_localXAlignment, nextYPos});
        nextYPos += group->inputField->getSize().y + textSize.y;
        group->inputField->render();
    }

    float buttonSpacing = m_size.y * 0.05f;
    m_button->setPos(
        m_currentPos.x + (m_button->getSize().x / 2.f),
        m_currentPos.y + nextYPos + buttonSpacing),
        m_button->render();
}

template <class EventType>
void BigView<EventType>::sendEvent()
{
    Log::info("BigView, sendEvent");
    if (!allInputFieldHasValidInput())
    {  
        //todo handle error event inside method call instead
        m_eventBus->fireEvent(AddMessageEvent(Texts::ERROR, Texts::NOT_VALID_INPUT));
        return;
    }

    Log::info("\tcreate recipe");
    Recipe recipe;
    recipe.name = m_inputGroups[0]->inputField->getText();
    recipe.reference = m_inputGroups[1]->inputField->getText();
    recipe.tags = m_inputGroups[2]->inputField->getText();

    Log::info("\tclearing input fields");
    for (InputGroup *group : m_inputGroups)
    {
        group->inputField->clear();
    }

    Log::info("Sending event");
    m_eventBus->fireEvent<EventType>(recipe);
}

template <class EventType>
bool BigView<EventType>::allInputFieldHasValidInput()
{
    for (InputGroup *group : m_inputGroups)
    {
        std::string text = group->inputField->getText();
        if (text.empty() || (!(text.find_first_not_of(' ') != std::string::npos)))
        {
            return false;
        }
    }
    return true;
}

#endif