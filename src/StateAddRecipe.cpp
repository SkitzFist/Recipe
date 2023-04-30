#include "StateAddRecipe.hpp"

#include "Settings.h"

StateAddRecipe::StateAddRecipe(EventBus* eventBus):
    State(eventBus){
    m_input = new InputField(Vector2{50.f, 100.f}, Vector2{500.f,50.f});
}

StateAddRecipe::~StateAddRecipe(){
    delete m_input;
}

void StateAddRecipe::handleInput(){
    m_input->handleInput();
}

void StateAddRecipe::update(float dt){
    m_input->update(dt);
}

void StateAddRecipe::render() const{
    m_input->render();
}
