#ifndef _ModifyRecipeView
#define _ModifyRecipeView

#include "View.h"

#include "Settings.h"

class ModifyRecipeView : public View{
public:
    ModifyRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos);
    ~ModifyRecipeView();

    /////////////////////////////
    ///  Inherited from view ///
    virtual void handleInput() override{}
    virtual void update(float dt) override{View::update(dt);}
    virtual void render() const override;
    ///////////////////////////
private:

};

#endif