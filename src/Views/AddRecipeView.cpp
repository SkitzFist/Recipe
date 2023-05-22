#include "AddRecipeView.h"

//debug
#include "Log.hpp"
#include "Settings.h"

AddRecipeView::AddRecipeView():
View(outOfViewPos, inViewPos, size){
}

AddRecipeView::~AddRecipeView(){
}

void AddRecipeView::handleInput(){

}

void AddRecipeView::update(const float dt){
    View::update(dt);
}

void AddRecipeView::render() const{
    BeginBlendMode(BLEND_ADDITIVE);
    DrawRectangle(m_currentPos.x, m_currentPos.y, size.x, size.y, Settings::VIEW_BACKGROUND_COLOR);  
    EndBlendMode();
}
