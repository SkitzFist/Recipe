#ifndef _Button
#define _Button

#include "Ui/UiButton.hpp"

#include "Settings.h"
#include "Collision.h"

class Button : public UiButton{

public:

    Button(Vector2 pos, Vector2 size, const std::string& text);
    Button(EventBus* eventBus,Vector2 pos, Vector2 size, const std::string& text, Event* event);
    ~Button();

    ///////////////////////////////////////////////////
    ////////   Inherited from UiButton
    virtual const Vector2& getSize() const override;
    virtual const Vector2& getPos() const override;
    virtual void setPos(Vector2 pos) override;
    virtual void handleInput() override;
    virtual void render() const override;
    virtual void setText(const std::string& text) override;
    virtual const std::string& getText() const override;
    /////////////////////////////////////////////////

private:
    Vector2 m_pos;
    Vector2 m_size;

    std::string m_text;
    int m_fontSize;
    bool m_isHovering;
};

////////////////////////////// IMPL /////////////////////////////////////////////////////
 Button::Button(EventBus* eventBus, Vector2 pos, Vector2 size, const std::string& text, Event* event): 
    m_eventBus(eventBus), m_pos(pos), m_size(size), m_text(text), m_isHovering(false), EVENT(event){

    m_fontSize = GetFontDefault().baseSize * 4.f;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);

    while (textSize.x > m_size.x || textSize.y > m_size.y)
    {
        m_fontSize *= 0.9f;
        textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);
    }
        
}


void Button::handleInput(){
    if (!m_visible)
        return;
    Vector2 mousePos = GetMousePosition();

    if (isColliding(mousePos, m_pos, m_size))
    {
        m_isHovering = true;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            
        }
    }
    else
    {
        m_isHovering = false;
    }
}

void Button::render() const{

    if(!isVisible()){
        return;
    }

    int segments = 64;
    Rectangle rec = {m_pos.x, m_pos.y, m_size.x, m_size.y};

    DrawRectangleRounded(rec, 1.0, segments, 
        m_isHovering ? Settings::BUTTON_HOVER_COLOR : Settings::BUTTON_COLOR
    );

    Font font = GetFontDefault();
    float posX = (m_pos.x + (m_size.x / 2.f)) - (MeasureTextEx(font, m_text.c_str(), m_fontSize, 2.0f).x / 2.f);
    float posY = (m_pos.y + (m_size.y / 2.f)) - (MeasureTextEx(font, m_text.c_str(), m_fontSize, 2.0).y / 2.f);
    DrawTextEx(font, m_text.c_str(), Vector2{posX, posY}, m_fontSize, 2.0, Settings::BUTTON_TEXT_COLOR);
}

const Vector2& Button::getSize() const{
    return m_size;
}

 const Vector2& Button::getPos() const{
    return m_pos;
}

void Button::setPos(Vector2 pos){
    m_pos = pos;
}

void Button::setText(const std::string& text){
    m_text = text;
}

const std::string& Button::getText() const{
    return m_text;
}


#endif