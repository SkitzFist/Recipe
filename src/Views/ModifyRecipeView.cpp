#include "ModifyRecipeView.h"

ModifyRecipeView::ModifyRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos, EventBus* eventBus) :
    View(outOfViewPos, inViewPos, Settings::BIG_PANEL_SIZE) ,m_eventBus(eventBus){
    
}

ModifyRecipeView::~ModifyRecipeView(){

}

void ModifyRecipeView::render() const{
    BeginBlendMode(BLEND_ADDITIVE);
        DrawRectangle(m_currentPos.x, m_currentPos.y, Settings::BIG_PANEL_SIZE.x, 
        Settings::BIG_PANEL_SIZE.y, Settings::VIEW_BACKGROUND_COLOR);  
    EndBlendMode();
}