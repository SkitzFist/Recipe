#include "StateSwitcher.hpp"

#include "StateStart.hpp"
#include "StateAddRecipe.hpp"

StateSwitcher::StateSwitcher(EventBus* eventBus) :
    EventHandler<SwitchStateToGenerateRecipe>(getNewId()), EventHandler<SwitchStateToAddRecipe>(getNewId()),
    EventHandler<SwitchStateToMainMenu>(getNewId()){
    
    eventBus->registerHandler<SwitchStateToAddRecipe>(this);
    eventBus->registerHandler<SwitchStateToGenerateRecipe>(this);
    eventBus->registerHandler<SwitchStateToMainMenu>(this);

    m_mainMenu = new StateStart(eventBus);
    m_addRecipe = new StateAddRecipe(eventBus);

    m_currentState = m_mainMenu;

}

StateSwitcher::~StateSwitcher(){
    m_currentState = nullptr;
    delete m_mainMenu;
    delete m_addRecipe;
    delete m_generateRecipe;
}

State* StateSwitcher::getCurrentState() const{
    return m_currentState;
}

void StateSwitcher::onEvent(const SwitchStateToGenerateRecipe& event){
    m_currentState = m_generateRecipe;
}

void StateSwitcher::onEvent(const SwitchStateToAddRecipe& event){
    m_currentState = m_addRecipe;
}

void StateSwitcher::onEvent(const SwitchStateToMainMenu& event){
    m_currentState = m_mainMenu;
}