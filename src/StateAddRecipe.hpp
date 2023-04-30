#ifndef _StateAddRecipe
#define _StateAddRecipe

#include "State.hpp"
#include "InputField.hpp"

class StateAddRecipe : public State{
public:
    StateAddRecipe(EventBus* eventBus);
    virtual ~StateAddRecipe() override;

    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

private:
    InputField* m_input;

};

#endif