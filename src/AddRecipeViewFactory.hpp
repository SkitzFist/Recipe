#ifndef _AddRecipeViewFactory
#define _AddRecipeViewFactory

#include "BigView.hpp"
namespace AddRecipeViewFactory{
    inline BigView<AddRecipeEvent>* create(EventBus* eventBus){
        Vector2 inViewPos = {
        Settings::VIEW_X_ALIGNMENT,(Settings::HEIGHT / 2.f) - (Settings::BIG_VIEW_SIZE.y / 2.f)
    };
    Vector2 outOfViewPos = {0 - Settings::BIG_VIEW_SIZE.x - 10.f, inViewPos.y};

    return new BigView<AddRecipeEvent>(outOfViewPos, inViewPos, eventBus, "Add Recipe", "Add");
    }
}

#endif