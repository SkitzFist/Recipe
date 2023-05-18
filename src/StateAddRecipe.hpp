#ifndef _StateAddRecipe
#define _StateAddRecipe

#include <memory>

#include "State.hpp"
#include "InputField.hpp"
#include "UiButton.hpp"

struct InputGroup
{
    std::string text = "";
    std::unique_ptr<InputField> inputField = nullptr;

    InputGroup(const std::string& _text, std::unique_ptr<InputField> _inputField)
        : text(_text), inputField(std::move(_inputField))
    {
    
    }

    const bool isFocused() const { return inputField->isFocused(); }
};


class StateAddRecipe : public State, EventHandler<PrepareAddRecipeEvent>, EventHandler<PrepareModifyRecipeEvent>,
    EventHandler<ClearInputEvent>, EventHandler<SearchFoundEvent>{
public:
    StateAddRecipe(EventBus* eventBus);
    virtual ~StateAddRecipe() override;

    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;
    void handleTab();

    ///////////////////////////////////////////////////////////////
    /// EventHandlers
    virtual void onEvent(const PrepareAddRecipeEvent& event) override;
    virtual void onEvent(const PrepareModifyRecipeEvent& event) override;
    virtual void onEvent(const ClearInputEvent& event) override;
    virtual void onEvent(const SearchFoundEvent& event) override;
    ///////////////////////////////////////////////////////////////

private:
    std::vector<std::unique_ptr<InputGroup>> m_inputGroups;
    const int getInputIndex(const std::string& groupName) const;

    UiButton* m_addRecipeButton;
    UiButton* m_modifyRecipeButton;
    UiButton* m_backButton;
    UiButton* m_clearButton;

    float m_buttonSpacing;
    
    void toggleState();

    ///////////////////////////////////////////////////////////////
    /// Event handling
    void handlePrepareAddRecipeEvent();
    void handlePrepareModifyRecipeEvent();
    const bool inputFieldsAreValid() const;
    const bool isValidEntry(const std::string& str) const;
    void handleClearInputEvent();
    void handlePrepareSearchRecipeEvent();
    //////////////////////////////////////////////////////////////
};

#endif