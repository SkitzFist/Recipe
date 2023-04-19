#ifndef _Button
#define _Button


#include "EventBus.hpp"

#include "UiElement.hpp"

template <class EventType>
class Button : public UiElement{
public:
    Button(Vector2 size, EventBus* eventBus, const char* text):
        m_pos{0,0},m_size(size), m_text(text), m_eventBus(eventBus), m_isHovering(false){}

    virtual ~Button()override{}

    void setPos(Vector2 pos){
        m_pos = pos;
    }

    virtual inline void onHover(bool isHovering) override{
        m_isHovering = isHovering;
    }

    virtual inline void onMouseReleased() override {
        log("on Release");
        m_eventBus->fireEvent(EventType());
        log("on Release");
    }

    virtual void render() const override{
        if(m_isHovering){
            Vector2 borderSize = Vector2{m_size.x * 1.05f, m_size.y * 1.2f};
            Vector2 borderPos = Vector2{
                m_pos.x - ((borderSize.x - m_size.x)/2.f),
                m_pos.y - ((borderSize.y - m_size.y)/2.f)
            };
            DrawRectangle(borderPos.x, borderPos.y, borderSize.x, borderSize.y, GREEN);
        }

        DrawRectangle(m_pos.x, m_pos.y, m_size.x, m_size.y, RAYWHITE);
        Font font = GetFontDefault();
        float posX = (m_pos.x + (m_size.x/2.f)) - (MeasureTextEx(font, m_text, font.baseSize * 4, 2.0).x/2.f);
        float posY = (m_pos.y + (m_size.y/2.f)) - (MeasureTextEx(font, m_text, font.baseSize * 4, 2.0).y/2.f);
        DrawTextEx(font, m_text, Vector2{posX, posY}, font.baseSize * 4, 2.0, RED);
    }

    virtual const Vector2& getSize() const override { return m_size; }
    virtual const Vector2& getPos() const override { return m_pos; }

private:
    Vector2 m_pos;
    Vector2 m_size;
    const char* m_text;
    EventBus* m_eventBus;
    bool m_isHovering;

};

#endif