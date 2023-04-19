#include "StateStart.hpp"
#include "Settings.h"
#include "Collision.h"
#include "Button.hpp"

#include "Log.hpp"

StateStart::StateStart(EventBus* _eventBus):
    State(_eventBus), EventHandler<AddRecipeButtonPressed>(getNewId()), m_state(this){

    m_eventBus->registerHandler<AddRecipeButtonPressed>(this);

    Button<AddRecipeButtonPressed>* addRecipeButton = new Button<AddRecipeButtonPressed>({250,50}, _eventBus, "Add Recipe");
    addRecipeButton->setPos(Vector2{
            (Settings::WIDTH / 2) - (addRecipeButton->getSize().x/2),
            ((int)(Settings::HEIGHT * 0.75)) - (addRecipeButton->getSize().y / 2)
        });

    m_uiElements.emplace_back(addRecipeButton);
    m_hoveredUiElement = nullptr;
    
}

StateStart::~StateStart(){
    for(int i = 0; i < m_uiElements.size(); ++i){
        delete m_uiElements[i];
    }
}

State* StateStart::handleInput(){
    
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
       
    return m_state;
}

State* StateStart::update(float dt){
    return m_state;
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

void StateStart::onEvent(const AddRecipeButtonPressed& _event){
    log("Button pressed");
}