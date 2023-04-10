#include "StateStart.hpp"
#include "Settings.h"
#include "raylib.h"


StateStart::StateStart(const EventBus& _eventBus):
    State(_eventBus), EventHandler<AddRecipeButtonPressed>(getNewId()), m_state(this){
    m_eventBus.registerHandler<AddRecipeButtonPressed>(this);        
}

StateStart::~StateStart(){

}

State* StateStart::handleInput(){
    
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
}

void StateStart::onEvent(const AddRecipeButtonPressed& _event){
    
}