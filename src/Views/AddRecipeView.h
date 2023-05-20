#ifndef _AddRecipeView
#define _AddRecipeView

#include "View.h"
#include "Settings.h"

inline constexpr Vector2 size = {Settings::WIDTH * 0.5f, Settings::HEIGHT * 0.5f};
inline constexpr Vector2 inViewPos {
    (Settings::WIDTH / 2.f) - (size.x / 2.f),
    (Settings::HEIGHT / 2.f) - (size.y / 2.f)
};
inline constexpr Vector2 outOfViewPos{
    0 - size.x - 10.f,
    inViewPos.y
};

class AddRecipeView : public View{
public:
    AddRecipeView();
    virtual ~AddRecipeView();

    virtual void handleInput() override;
    virtual void update(const float dt) override;
    virtual void render() const override;

private:

};

#endif