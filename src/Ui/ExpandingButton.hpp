#ifndef _ExpandingButton
#define _ExpandingButton

#include "UiButton.hpp"
#include "Collision.h"

class ExpandingButton : public UiButton{
public:
    ExpandingButton(Vector2 size, const std::string& text, Vector2 pos = Vector2{0.f,0.f}):
        m_pos(pos), m_collapsedSize(size), m_expandedSize{0.f,0.f},m_text(text), m_isHovering(false){
            fontSize = GetFontDefault().baseSize * 4;
            Vector2 textSize = MeasureTextEx(GetFontDefault(), text.substr(0,1).c_str(), fontSize, 2.f);
            while (textSize.x >= m_collapsedSize.x || textSize.y >= m_collapsedSize.y)
            {
                fontSize *= 0.95;
                textSize = MeasureTextEx(GetFontDefault(), text.substr(0,1).c_str(), fontSize, 2.f);
            }

            m_expandedSize.y = m_collapsedSize.y;

        
            m_expandedSize.x = (MeasureTextEx(GetFontDefault(), m_text.c_str(), fontSize, 2.f).x) * 1.2f;
        }

    virtual ~ExpandingButton()override{}

    virtual void handleInput() override{
        if(!m_visible)
            return;
        Vector2 mousePos = GetMousePosition();

        if(isColliding(mousePos, m_pos, m_collapsedSize)){
            m_isHovering = true;
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                onClick.emit();
            }
        }else{
            m_isHovering = false;
        }
    }

    virtual void render() const override{
        if(!m_visible){
            return;
        }
        float roundness = 1.0f;
            int segments = 256;

        //draw button
        if(m_isHovering){
            Rectangle rec{ m_pos.x, m_pos.y, m_expandedSize.x, m_expandedSize.y};
            DrawRectangleRounded(rec, roundness, segments, Settings::BUTTON_HOVER_COLOR);
        }else{
            Rectangle rec = {m_pos.x, m_pos.y, m_collapsedSize.x, m_collapsedSize.y};
            DrawRectangleRounded(rec, roundness, segments, Settings::BUTTON_COLOR);
        }

        //draw text
        if(m_isHovering){
            renderString(m_text, m_expandedSize);
        }else{
            renderString(m_text.substr(0,1), m_collapsedSize);
        }
    }

    void renderString(const std::string& text, Vector2 size)const{
        Font font = GetFontDefault();
        float posX = (m_pos.x + (size.x/2.f)) - (MeasureTextEx(font, text.c_str(), fontSize, 2.0f).x/2.f);
        float posY = (m_pos.y + (size.y/2.f)) - (MeasureTextEx(font, text.c_str(), fontSize, 2.0).y/2.f);
        DrawTextEx(font, text.c_str(), Vector2{posX, posY}, fontSize, 2.0, Settings::BUTTON_TEXT_COLOR);
    }

    virtual const Vector2& getSize() const override { return m_collapsedSize; }
    virtual const Vector2& getPos() const override { return m_pos; }
    virtual void setPos(Vector2 pos) override { m_pos = pos; }
    
    virtual void setText(const std::string& text) override {m_text = text;}
    virtual const std::string& getText() const override {return m_text;}

private:
    float fontSize;
    Vector2 m_pos;
    Vector2 m_collapsedSize;
    Vector2 m_expandedSize;
    std::string m_text;
    bool m_isHovering;
};

#endif