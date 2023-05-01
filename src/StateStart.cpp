#include "StateStart.hpp"
#include "Settings.h"
#include "Collision.h"
#include "Button.hpp"

#include "Log.hpp"

StateStart::StateStart(EventBus* _eventBus):
    State(_eventBus){

    Button<SwitchStateToAddRecipe>* addRecipeButton = new Button<SwitchStateToAddRecipe>({250,50}, _eventBus, "Add Recipe");
    addRecipeButton->setPos(Vector2{
            (Settings::WIDTH / 2) - (addRecipeButton->getSize().x/2),
            ((int)(Settings::HEIGHT * 0.75)) - (addRecipeButton->getSize().y / 2)
        });


    Button<SwitchStateToGenerateRecipe>* generateRecipeButton = new Button<SwitchStateToGenerateRecipe>({250,50}, _eventBus, "Generate recipe");
    generateRecipeButton->setPos(Vector2{
            addRecipeButton->getPos().x, 
            addRecipeButton->getPos().y - 100.f
        });

    m_uiElements.emplace_back(addRecipeButton);
    m_uiElements.emplace_back(generateRecipeButton);
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
    const char* title = "Recept generator";
    int fontSize = 32;
    int width = MeasureText(title, fontSize) / 2;
    DrawTextEx(GetFontDefault(), title, Vector2{Settings::WIDTH/2.f - width, 5.f}, fontSize, 2.f,DARKGRAY);

    for(UiButton* button : m_uiElements){
        button->render();
    }
}