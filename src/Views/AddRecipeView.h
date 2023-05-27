#ifndef _AddRecipeView
#define _AddRecipeView

#include <vector>
#include <memory>

#include "View.h"

#include "Array.hpp"
#include "Settings.h"

class AddRecipeView : public View{
public:
    AddRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos);
    virtual ~AddRecipeView();

    virtual void handleInput() override;
    virtual void update(const float dt) override;
    virtual void render() const override;

    void onAddRecipe();
private:
    Array<InputGroup*> m_inputGroups;
    float m_localXAlignment;
};

#endif