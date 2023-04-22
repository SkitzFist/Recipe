#ifndef _StateSwitcher
#define _StateSwitcher

#include "State.hpp"

class StateSwitcher : public EventHandler<GenerateRecipePressed>, public EventHandler<AddRecipePressed>{
public:
    StateSwitcher(EventBus* eventBus);
    State* getCurrentState() const;

    virtual void onEvent(const GenerateRecipePressed& event) override;
    virtual void onEvent(const AddRecipePressed& event) override;
private:
    State* m_state;

};

#endif