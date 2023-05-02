#include "StateStart.hpp"
#include "Settings.h"
#include "Collision.h"
#include "Button.hpp"

#include "Log.hpp"

StateStart::StateStart(EventBus* _eventBus):
    State(_eventBus){

    Button<SwitchStateToGenerateRecipe>* generateRecipeButton = new Button<SwitchStateToGenerateRecipe>({250,50}, _eventBus, "Generate recipe");
    Button<SwitchStateToAddRecipe>* addRecipeButton = new Button<SwitchStateToAddRecipe>({250,50}, _eventBus, "Add Recipe");
    m_uiElements.emplace_back(generateRecipeButton);
    m_uiElements.emplace_back(addRecipeButton);
}

StateStart::~StateStart(){
    for(std::size_t i = 0; i < m_uiElements.size(); ++i){
        delete m_uiElements[i];
    }
}

void StateStart::handleInput(){
    
    for(UiButton* button : m_uiElements){
        button->handleInput();
    }
       
}

void StateStart::update(float dt){
    
}

void StateStart::render() const{
    const char* title = "Recept";
    int fontSize = 32;
    int width = MeasureText(title, fontSize) / 2;
    DrawTextEx(GetFontDefault(), title, Vector2{Settings::WIDTH/2.f - width, 5.f}, fontSize, 2.f,DARKGRAY);


    float buttonYSpacing = m_uiElements[0]->getSize().y * 1.5f;
    float nextYPos = (Settings::HEIGHT / 2.f) - buttonYSpacing;
    float nextXPos = (Settings::WIDTH / 2.f) - (m_uiElements[0]->getSize().x / 2.f);
    
    for(UiButton* button : m_uiElements){
        button->setPos(nextXPos, nextYPos);
        button->render();

        nextYPos += buttonYSpacing;
    }
}