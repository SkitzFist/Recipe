#ifndef _ModifyRecipeView
#define _ModifyRecipeView

#include "View.h"

#include "Settings.h"
#include "EventBus.hpp"

class ModifyRecipeView : public View{
public:
    ModifyRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos, EventBus* eventBus);
    ~ModifyRecipeView();

    /////////////////////////////
    ///  Inherited from view ///
    virtual void handleInput() override{}
    virtual void update(float dt) override{View::update(dt);}
    virtual void render() const override;
    ///////////////////////////
private:
    EventBus* m_eventBus;

};

#endif