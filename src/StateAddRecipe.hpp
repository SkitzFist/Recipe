#ifndef _StateAddRecipe
#define _StateAddRecipe

#include "State.hpp"
#include "InputField.hpp"
#include "UiButton.hpp"

struct InputGroup
{
    std::string text = "";
    InputField* inputField = nullptr;

    InputGroup(const std::string& _text, InputField*_inputField){
        text = _text;
        inputField = _inputField;
    }
};


class StateAddRecipe : public State, EventHandler<PrepareAddRecipe>{
public:
    StateAddRecipe(EventBus* eventBus);
    virtual ~StateAddRecipe() override;

    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;
    void handleTab();
    virtual void onEvent(const PrepareAddRecipe& event) override;
    void handlePrepareAddRecipeEvent();

private:
    std::vector<InputGroup> m_inputGroups;
    std::vector<UiButton*> m_buttons;

    const bool validEntry(const std::string& str) const;
};

#endif