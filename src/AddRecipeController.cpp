#include "AddRecipeController.hpp"

AddRecipeController::AddRecipeController(EventBus* eventBus, BigView<AddRecipeEvent>* view):
    m_eventBus(eventBus), m_view(view){
}

AddRecipeController::~AddRecipeController(){
    delete m_view;
}

void AddRecipeController::handleUpdate(){
    m_view->handleInput();
}

void AddRecipeController::update(float dt){
    m_view->update(dt);
}

void AddRecipeController::render() const{
    m_view->render();
}

void AddRecipeController::show(){
    m_view->show();
}

void AddRecipeController::hide(){
    m_view->hide();
}

