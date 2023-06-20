#ifndef _ModifyRecipeViewFactory
#define _ModifyRecipeViewFactory

#include "BigView.hpp"

namespace ModifyRecipeViewFactory{
    inline BigView<ModifyRecipePreparParameters>* create(EventBus* eventBus){
        Vector2 inViewPos = {
            Settings::VIEW_X_ALIGNMENT, 
            (Settings::HEIGHT / 2.f) - (Settings::BIG_VIEW_SIZE.y / 2.f)
        };
        Vector2 outOfViewPos = {Settings::WIDTH + Settings::BIG_VIEW_SIZE.x, inViewPos.y};

        return new BigView<ModifyRecipePreparParameters>(outOfViewPos, inViewPos, eventBus, "Modify Recipe", "Modify");
    }
}

#endif