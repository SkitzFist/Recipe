#ifndef _AddRecipeView
#define _AddRecipeView

#include <vector>
#include <memory>

#include "View.h"

#include "Settings.h"
#include "Transmission/EventBus.hpp"
#include "Ui/UiButton.hpp"
#include "TabCycling.h"

class AddRecipeView : public View{
public:
    AddRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos, EventBus* eventBus);
    virtual ~AddRecipeView();

    virtual void handleInput() override;
    virtual void update(const float dt) override;
    virtual void render() const override;

    void onAddRecipe();
private:
    EventBus* m_eventBus;
    float m_localXAlignment;
    
    Array<InputGroup*> m_inputGroups;
    TabCycling m_tabCycling;
    UiButton* m_addButton;

    bool allInputFieldHasValidInput();
};

#endif