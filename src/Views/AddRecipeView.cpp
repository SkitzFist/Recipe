#include "AddRecipeView.h"

//debug
#include "Log.hpp"

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
    DrawRectangle(m_currentPos.x, m_currentPos.y, m_size.x, m_size.y, SKYBLUE);
}
