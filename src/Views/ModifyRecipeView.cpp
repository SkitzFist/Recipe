#include "ModifyRecipeView.h"

ModifyRecipeView::ModifyRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos) :
    View(outOfViewPos, inViewPos, Settings::BIG_VIEW_SIZE){
    
}

ModifyRecipeView::~ModifyRecipeView(){

}

void ModifyRecipeView::render() const{
    BeginBlendMode(BLEND_ADDITIVE);
        DrawRectangle(m_currentPos.x, m_currentPos.y, Settings::BIG_VIEW_SIZE.x, 
        Settings::BIG_VIEW_SIZE.y, Settings::VIEW_BACKGROUND_COLOR);  
    EndBlendMode();
}