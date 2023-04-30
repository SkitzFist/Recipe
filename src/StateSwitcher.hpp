#ifndef _StateSwitcher
#define _StateSwitcher

#include "State.hpp"

class StateSwitcher : 
    public EventHandler<SwitchStateToGenerateRecipe>, public EventHandler<SwitchStateToAddRecipe>,
    public EventHandler<SwitchStateToMainMenu>{

public:
    StateSwitcher(EventBus* eventBus);
    ~StateSwitcher();
    State* getCurrentState() const;

    virtual void onEvent(const SwitchStateToGenerateRecipe& event) override;
    virtual void onEvent(const SwitchStateToAddRecipe& event) override;
    virtual void onEvent(const SwitchStateToMainMenu& event) override;
private:
    State* m_currentState;
    State* m_mainMenu;
    State* m_addRecipe;
    State* m_generateRecipe;
};

#endif