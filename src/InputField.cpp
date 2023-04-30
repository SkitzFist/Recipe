#include "InputField.hpp"

#include "Log.hpp"
#include "Collision.h"
#include <cstring>

InputField::InputField(Vector2 pos, Vector2 size):
    m_pos(pos), m_size(size), m_text(""), BLINK_TIME(1.0f), m_blinkTimer(0.0f), m_carrotVisible(false),
    m_carrotPos(0), REMOVAL_COOLDOWN_START(0.2f), m_removalTimer(0.f), m_removalInProgress(false), m_removalElapsed(0.0f),
    m_markTextInProgress(false), m_markTextStartPos{0.f,0.f}, m_markTextIndexes{0,0}{

    m_fontSize = GetFontDefault().baseSize * 4;
    m_textMarkerBox.size.y = MeasureTextEx(GetFontDefault(), "A", m_fontSize, 2.f).y;
    m_textMarkerBox.pos.y = (m_pos.y + (m_size.y / 2.)) - (m_textMarkerBox.size.y / 2.f);
}

InputField::~InputField(){

}

void InputField::handleInput(){
    handleCarrotOffset();
    handleTextInput();
    handleRemoveBackward();
    handleMarkText();

    if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V)){
        m_text.insert(m_carrotPos, GetClipboardText());
        m_carrotPos += std::strlen(GetClipboardText());
    }
}

void InputField::handleCarrotOffset(){
    size_t offset = 0;
    if(IsKeyPressed(KEY_LEFT)){
        offset -= 1;
    }

    if(IsKeyPressed(KEY_RIGHT)){
        offset += 1;
    }

    if(offset == 0){
        return;
    }

    int newPos = m_carrotPos + offset;
    if(canMoveCarrot(newPos)){
        removeCarrot();
        m_carrotPos = newPos;
        placeCarrotAt(m_carrotPos);
    }
}

const bool InputField::canMoveCarrot(int pos) const{
    return pos >= 0 && pos < m_text.size();
}

void InputField::handleTextInput(){
    int unicode = GetCharPressed();
    if(unicode > 0){
        removeCarrot();
    }
    while (unicode > 0)
    {  
        char code[2];
        code[0] = (char)unicode;
        code[1] = '\0';
        m_text.insert(m_carrotPos, code);
        m_carrotPos += 1;
        unicode = GetCharPressed();
    }
}

void InputField::handleRemoveBackward(){

    if(IsKeyPressed(KEY_BACKSPACE)){
        m_removalInProgress = true;
        removeCarrot();
    }

    while (canRemoveBackwards())
    {
        m_text.erase(m_carrotPos -1, 1);
        m_removalTimer = REMOVAL_COOLDOWN_START / (m_removalElapsed + 1.f);
        m_carrotPos -= 1;
    }
    
    if(IsKeyReleased(KEY_BACKSPACE)){
        m_removalInProgress = false;
        m_removalElapsed = 0.0f;
    }
}

bool InputField::canRemoveBackwards() const{
    return IsKeyDown(KEY_BACKSPACE) && !m_text.empty() && m_removalTimer < 0.f && m_removalInProgress && m_carrotPos != 0;
}

void InputField::handleMarkText(){

    //engage marking text
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        removeCarrot();
        Vector2 textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);
        Vector2 textPos = getTextPos();
        Vector2 mousePos = GetMousePosition();

        if(isColliding(mousePos, textPos, textSize)){
            m_markTextInProgress = true;
            m_markTextStartPos = mousePos;
            float deltaX = mousePos.x - textPos.x;
            float percentageX = deltaX / textSize.x;
            m_markTextIndexes.x = static_cast<int>(percentageX * m_text.size());
        }
    }

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        m_markTextInProgress = false;

        Vector2 textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);
        Vector2 textPos = getTextPos();
        Vector2 mousePos = GetMousePosition();

        float deltaX = mousePos.x - textPos.x;
        float percentageX = deltaX / textSize.x;
        int index = static_cast<int>(percentageX * m_text.size());
        
        if(index >= m_text.size()){
            index = m_text.size() - 1;
        }else if(index < 0){
            index = 0;
        }

        m_markTextIndexes.y = index;

        if(m_markTextIndexes.y < m_markTextIndexes.x){
            int tmp = m_markTextIndexes.x;
            m_markTextIndexes.x = m_markTextIndexes.y;
            m_markTextIndexes.y = tmp;
        }
        
        std::string str = m_text.substr(m_markTextIndexes.x, (m_markTextIndexes.y - m_markTextIndexes.x) + 1);
        
        std::size_t charIndex = str.find("|");
        while (charIndex != -1)
        {
            str.erase(charIndex, 1);
            charIndex = str.find("|");
        }
        
        SetClipboardText(str.c_str());
        GetClipboardText(); //weird bug where it doesn't always get saved to clipboard unless being called upon.
        clearMarkText();
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && m_markTextInProgress){
        Vector2 mousePos = GetMousePosition();

        if(m_markTextStartPos.x < mousePos.x){
           m_textMarkerBox.pos.x = m_markTextStartPos.x;
           if(m_textMarkerBox.pos.x > (m_pos.x + m_size.x)){
                m_textMarkerBox.pos.x = m_pos.x + m_size.x;
           }
           m_textMarkerBox.size.x = mousePos.x - m_markTextStartPos.x;
        }else{
            m_textMarkerBox.pos.x = mousePos.x;
            if(m_textMarkerBox.pos.x < m_pos.x){
                m_textMarkerBox.pos.x = m_pos.x;
            }
            m_textMarkerBox.size.x = m_markTextStartPos.x - mousePos.x;
        }
    }
}

void InputField::clearMarkText(){
    m_markTextIndexes = {0,0};
    m_markTextStartPos = {0.f, 0.f};
    m_textMarkerBox.pos.x = 0.f;
    m_textMarkerBox.size.x = 0.f;
    m_markTextInProgress = false;
}

void InputField::update(float dt){
    if(!m_removalInProgress){
        updateCarrot(dt);   
    }

    m_removalTimer -= dt;
    if(m_removalInProgress){
        m_removalElapsed += dt;
    }
}

void InputField::updateCarrot(float dt){
    m_blinkTimer -= dt;
    if(m_blinkTimer < 0.0 && (!m_markTextInProgress || !m_removalInProgress)){
        if(m_carrotVisible){
            removeCarrot();
        }else{
            placeCarrotAt(m_carrotPos);
            m_carrotVisible = true;
        }
    }
}

void InputField::placeCarrotAt(int index){
    m_text.insert(index, "|");
    m_carrotVisible = true;
    m_blinkTimer = BLINK_TIME;
}

void InputField::removeCarrot(){
    std::size_t index = m_text.find("|");
    while (index != -1){
        m_text.erase(index, 1);
        index = m_text.find("|");
    }
    m_carrotVisible = false;
    m_blinkTimer = BLINK_TIME;
}

void InputField::render() const{
    DrawRectangle(m_pos.x, m_pos.y, m_size.x, m_size.y, RAYWHITE);


    DrawRectangle(m_textMarkerBox.pos.x, m_textMarkerBox.pos.y, m_textMarkerBox.size.x, m_textMarkerBox.size.y, BLUE);

    Font font = GetFontDefault();
    float posX = (m_pos.x + 2.f);
    float posY = (m_pos.y + (m_size.y/2.f)) - (MeasureTextEx(font, m_text.c_str(), m_fontSize, 2.0).y/2.f);
    DrawTextEx(font, m_text.c_str(), Vector2{posX, posY}, m_fontSize, 2.0, BLACK);
}

void InputField::onFocus(){
    m_blinkTimer = BLINK_TIME;
}

void InputField::onBlur(){

}

Vector2 InputField::getTextPos(){
    Vector2 textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);
    return {m_pos.x + 2.f, (m_pos.y + (m_size.y/2.f)) - (textSize.y/2.f)};
}