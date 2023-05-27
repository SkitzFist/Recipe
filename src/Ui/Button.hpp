#ifndef _Button
#define _Button

#include "Ui/UiButton.hpp"

#include "Settings.h"

class Button : public UiButton{
public:

    Button(Vector2 pos, Vector2 size, const std::string& text);
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

    bool m_isHovering;
};

 Button::Button(Vector2 pos, Vector2 size, const std::string& text): 
    m_pos(pos), m_size(size), m_text(text), m_isHovering(false){

    }


void Button::handleInput(){

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