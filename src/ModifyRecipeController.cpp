#include "ModifyRecipeController.hpp"

ModifyRecipeController::ModifyRecipeController(EventBus* eventBus, BigView<ModifyRecipePreparParameters>* view) : 
    m_eventBus(eventBus), m_view(view){

    clearRecipe();
    m_eventBus->registerHandler<ModifyRecipePrepareId>(this);
    m_eventBus->registerHandler<ModifyRecipePreparParameters>(this);
}

ModifyRecipeController::~ModifyRecipeController(){
    delete m_view;
}

void ModifyRecipeController::handleInput(){
    m_view->handleInput();
}

void ModifyRecipeController::update(float dt){
    m_view->update(dt);
}

void ModifyRecipeController::render() const{
    m_view->render();
}

void ModifyRecipeController::show(){
    m_view->show();
}

void ModifyRecipeController::clearRecipe(){
    m_recipe.id = -1;
    m_recipe.name = "";
    m_recipe.reference = "";
    m_recipe.tags = "";
}

void ModifyRecipeController::sendEvent(){
    m_eventBus->fireEvent(ModifyRecipeEvent(m_recipe));
}

void ModifyRecipeController::onEvent(const ModifyRecipePrepareId& event){
    clearRecipe();

    m_recipe.id = event.id;
}

void ModifyRecipeController::onEvent(const ModifyRecipePreparParameters& event){
    m_recipe.name = event.recipe.name;
    m_recipe.reference = event.recipe.reference;
    m_recipe.tags = event.recipe.tags;

    sendEvent();
}