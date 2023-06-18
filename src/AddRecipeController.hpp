#ifndef _AddRecipeController
#define _AddRecipeController

#include "Transmission/EventBus.hpp"
#include "BigView.hpp"

class AddRecipeController{
public:
    AddRecipeController(BigView<AddRecipeEvent> view);

private:
    BigView<AddRecipeEvent> m_view;
};

#endif