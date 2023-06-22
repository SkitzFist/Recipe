#ifndef _ModifyRecipeController
#define _ModifyRecipeController

#include "Transmission/EventBus.hpp"
#include "BigView.hpp"

class ModifyRecipeController : 
    public EventHandler<ModifyRecipePrepareId>, 
    public EventHandler<ModifyRecipePreparParameters>{
public:
    ModifyRecipeController(EventBus* eventBus, BigView<ModifyRecipePreparParameters>* view);
    ~ModifyRecipeController();

    void handleInput();
    void update(float dt);
    void render() const;

    void show();
    void hide();
    
private:
    Recipe m_recipe;
    EventBus* m_eventBus;
    BigView<ModifyRecipePreparParameters>* m_view;

    void clearRecipe();
    void sendEvent();

    //________________________//
    //       EventHandler    //
    virtual void onEvent(const ModifyRecipePrepareId& event) override;
    virtual void onEvent(const ModifyRecipePreparParameters& event) override;
    //_____________________//
};

#endif