#include "StateStart.hpp"
#include "Settings.h"
#include "Collision.h"
#include "Button.hpp"

#include "Log.hpp"

StateStart::StateStart(EventBus* _eventBus):
    State(_eventBus){
    
    Vector2 buttonSize = {250, 50};
    Button<SwitchStateToGenerateRecipe>* generateRecipeButton = new Button<SwitchStateToGenerateRecipe>(buttonSize, _eventBus, "Generate recipe");
    Button<SwitchStateToAddRecipe>* addRecipeButton = new Button<SwitchStateToAddRecipe>(buttonSize, _eventBus, "Add Recipe");
    m_buttons.emplace_back(generateRecipeButton);
    m_buttons.emplace_back(addRecipeButton);
}

StateStart::~StateStart(){
    for(std::size_t i = 0; i < m_buttons.size(); ++i){
        delete m_buttons[i];
    }
}

void StateStart::handleInput(){
    for(UiButton* button : m_buttons){
        button->handleInput();
    }
       
}

void StateStart::update(float dt){
    
}

void StateStart::render() const{
    float buttonYSpacing = m_buttons[0]->getSize().y * 1.5f;
    float nextYPos = (Settings::HEIGHT / 2.f) - buttonYSpacing;
    float nextXPos = (Settings::WIDTH / 2.f) - (m_buttons[0]->getSize().x / 2.f);
    
    for(UiButton* button : m_buttons){
        button->setPos(nextXPos, nextYPos);
        button->render();

        nextYPos += buttonYSpacing;
    }

    const char* title = "Recept";
    int fontSize = 32 * 2;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), title, fontSize, 2.f);
    Vector2 textPos = {
        m_buttons[0]->getPos().x + ((m_buttons[0]->getSize().x - textSize.x) / 2.f),
        Settings::HEIGHT / 4.f
    };
    DrawTextEx(GetFontDefault(), title, textPos, fontSize, 2.f, TITLE_COLOR);
}