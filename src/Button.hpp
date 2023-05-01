#ifndef _Button
#define _Button

#include "EventBus.hpp"
#include "UiButton.hpp"
#include "Collision.h"

template <class EventType>
class Button : public UiButton{
public:
    Button(Vector2 size, EventBus* eventBus, const char* text):
        m_pos{0,0},m_size(size), m_text(text), m_eventBus(eventBus), m_isHovering(false){
            fontSize = GetFontDefault().baseSize * 4;
            Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 2.f);
            while (textSize.x >= m_size.x || textSize.y >= m_size.y)
            {
                fontSize *= 0.95;
                textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 2.f);
            }
            
        }

    virtual ~Button()override{}

    virtual void handleInput() override{
        Vector2 mousePos = GetMousePosition();

        if(isColliding(mousePos, m_pos, m_size)){
            m_isHovering = true;
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                m_eventBus->fireEvent(EventType());
            }
        }else{
            m_isHovering = false;
        }
    }

    virtual void render() const override{
        if(m_isHovering){
            Vector2 borderSize = Vector2{m_size.x * 1.025f, m_size.y * 1.1f};
            Vector2 borderPos = Vector2{
                m_pos.x - ((borderSize.x - m_size.x)/2.f),
                m_pos.y - ((borderSize.y - m_size.y)/2.f)
            };
            DrawRectangle(borderPos.x, borderPos.y, borderSize.x, borderSize.y, ORANGE);
            
        }

        DrawRectangle(m_pos.x, m_pos.y, m_size.x, m_size.y, RAYWHITE);
        Font font = GetFontDefault();
        float posX = (m_pos.x + (m_size.x/2.f)) - (MeasureTextEx(font, m_text, fontSize, 2.0).x/2.f);
        float posY = (m_pos.y + (m_size.y/2.f)) - (MeasureTextEx(font, m_text, fontSize, 2.0).y/2.f);
        DrawTextEx(font, m_text, Vector2{posX, posY}, fontSize, 2.0, DARKGRAY);
    }

    virtual const Vector2& getSize() const override { return m_size; }
    virtual const Vector2& getPos() const override { return m_pos; }
    void setPos(Vector2 pos){ m_pos = pos; }

private:
    float fontSize;
    Vector2 m_pos;
    Vector2 m_size;
    const char* m_text;
    EventBus* m_eventBus;
    bool m_isHovering;

};

#endif