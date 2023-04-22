#include "StateSwitcher.hpp"

#include "StateStart.hpp"

StateSwitcher::StateSwitcher(EventBus* eventBus) :
    EventHandler<GenerateRecipePressed>(getNewId()), EventHandler<AddRecipePressed>(getNewId()){
    
    m_state = new StateStart(eventBus);

}

State* StateSwitcher::getCurrentState() const{
    return m_state;
}

void StateSwitcher::onEvent(const GenerateRecipePressed& event){

}

void StateSwitcher::onEvent(const AddRecipePressed& event){

}
