#ifndef _AddRecipeController
#define _AddRecipeController

#include "Transmission/EventBus.hpp"
#include "BigView.hpp"

class AddRecipeController{
public:
    AddRecipeController(EventBus* eventBus, BigView<AddRecipeEvent>* view);
    ~AddRecipeController();
    
    void handleUpdate();
    void update(float dt);
    void render() const;

    void show();
    void hide();

private:
    EventBus* m_eventBus;
    BigView<AddRecipeEvent>* m_view;

};

#endif