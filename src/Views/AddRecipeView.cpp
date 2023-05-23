#include "AddRecipeView.h"

//debug
#include "Log.hpp"
#include "Settings.h"

AddRecipeView::AddRecipeView(EventBus* eventBus):
View(outOfViewPos, inViewPos, size){

    Vector2 inputFieldSize = {
        size.x * 0.9f,
        size.y * 0.05
    };

    m_localXAlignment = (size.x / 2.f) - (inputFieldSize.x / 2.f);

    m_inputGroups.emplace_back(
        std::make_unique<InputField>(inputFieldSize, eventBus),
        "Name"
    );

    m_inputGroups.emplace_back(
        std::make_unique<InputField>(inputFieldSize, eventBus),
        "Reference"
    );
    
    m_inputGroups.emplace_back(
        std::make_unique<InputField>(inputFieldSize, eventBus),
        "Tags"
    );
}

AddRecipeView::~AddRecipeView(){
}

void AddRecipeView::handleInput(){
    for(InputGroup& group : m_inputGroups){
        group.inputField->handleInput();
    }
}

void AddRecipeView::update(const float dt){
    View::update(dt);

    for(InputGroup& group : m_inputGroups){
        group.inputField->update(dt);
    }
}

void AddRecipeView::render() const{
    BeginBlendMode(BLEND_ADDITIVE);
        DrawRectangle(m_currentPos.x, m_currentPos.y, size.x, size.y, Settings::VIEW_BACKGROUND_COLOR);  
    EndBlendMode();

    float nextYPos = m_size.y * 0.2f;
    for(const InputGroup& group : m_inputGroups){
        
        float fontSize = GetFontDefault().baseSize * 4.f;
        DrawTextEx(GetFontDefault(), group.title.c_str(), {m_currentPos.x + m_localXAlignment, nextYPos}, 
        fontSize, 2.f, Settings::BUTTON_TEXT_COLOR);
        Vector2 textSize = MeasureTextEx(GetFontDefault(), group.title.c_str(), fontSize, 2.f);
        nextYPos += textSize.y * 1.2f;
        group.inputField->setPos({m_currentPos.x + m_localXAlignment, nextYPos});
        nextYPos += group.inputField->getSize().y + textSize.y;
        group.inputField->render();
    }
}
