#include "AddRecipeView.h"

#include "Settings.h"

//debug
#include "Log.hpp"

AddRecipeView::AddRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos):
View(outOfViewPos, inViewPos, Settings::BIG_PANEL_SIZE), m_inputGroups(3){

    Vector2 inputFieldSize = {
        Settings::BIG_PANEL_SIZE.x * 0.9f,
        Settings::BIG_PANEL_SIZE.y * 0.05
    };

    m_localXAlignment = (Settings::BIG_PANEL_SIZE.x / 2.f) - (inputFieldSize.x / 2.f);

    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Name"
    ));

    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Reference"
    ));
    
    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Tags"
    ));

}

AddRecipeView::~AddRecipeView(){
    m_inputGroups.clear();
}

void AddRecipeView::handleInput(){
    for(InputGroup* group : m_inputGroups){
        group->inputField->handleInput();
    }
}

void AddRecipeView::update(const float dt){
    View::update(dt);

    for(InputGroup* group : m_inputGroups){
        group->inputField->update(dt);
    }
}

void AddRecipeView::render() const{
    BeginBlendMode(BLEND_ADDITIVE);
        DrawRectangle(m_currentPos.x, m_currentPos.y, Settings::BIG_PANEL_SIZE.x, 
        Settings::BIG_PANEL_SIZE.y, Settings::VIEW_BACKGROUND_COLOR);  
    EndBlendMode();

    float nextYPos = m_size.y * 0.2f;
    for(const InputGroup* group : m_inputGroups){
        float fontSize = GetFontDefault().baseSize * 4.f;
        DrawTextEx(GetFontDefault(), group->title.c_str(), {m_currentPos.x + m_localXAlignment, nextYPos}, fontSize, 2.f, Settings::BUTTON_TEXT_COLOR);
        Vector2 textSize = MeasureTextEx(GetFontDefault(), group->title.c_str(), fontSize, 2.f);
        nextYPos += textSize.y * 1.2f;
        group->inputField->setPos({m_currentPos.x + m_localXAlignment, nextYPos});
        nextYPos += group->inputField->getSize().y + textSize.y;
        group->inputField->render();
    }
}
