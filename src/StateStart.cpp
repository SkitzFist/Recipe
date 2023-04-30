#include "StateStart.hpp"
#include "Settings.h"
#include "Collision.h"
#include "Button.hpp"

#include "Log.hpp"

StateStart::StateStart(EventBus* _eventBus):
    State(_eventBus), m_state(this){

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

    m_hoveredUiElement = nullptr;
    
}

StateStart::~StateStart(){
    for(int i = 0; i < m_uiElements.size(); ++i){
        delete m_uiElements[i];
    }
}

void StateStart::handleInput(){
    
    if(m_hoveredUiElement){
        m_hoveredUiElement->onHover(isColliding(GetMousePosition(), m_hoveredUiElement->getPos(), m_hoveredUiElement->getSize()));
    }

    for(std::size_t i = 0; i < m_uiElements.size(); ++i){
        if(isColliding(GetMousePosition(), m_uiElements[i]->getPos(), m_uiElements[i]->getSize())){
            m_uiElements[i]->onHover(true);
            m_hoveredUiElement = m_uiElements[i];

            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                m_uiElements[i]->onMouseReleased();
            }
        }
    }
       
}

void StateStart::update(float dt){
    
}

void StateStart::render() const{
    const char* title = "Recept generator";
    int fontSize = 20;
    int width = MeasureText(title, fontSize) / 2;
    DrawText(title, Settings::WIDTH/2 - width, 5, fontSize, RAYWHITE);

    for(std::size_t i = 0; i < m_uiElements.size(); ++i){
        m_uiElements[i]->render();    
    }
}