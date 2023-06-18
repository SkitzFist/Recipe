#include "Button.hpp"

//debug
#include "Log.hpp"

Button::Button(Vector2 pos, Vector2 size, const std::string& text): 
   m_pos(pos), m_size(size), m_text(text), m_isHovering(false){
    Log::info("Button cstr");
    m_fontSize = GetFontDefault().baseSize * 4.f;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);

    //shrink fontsize if text is bigger then bgr
    while (textSize.x > m_size.x || textSize.y > m_size.y)
    {
        m_fontSize *= 0.9f;
        textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);
    }
        
}

Button::Button(Button&& src) noexcept:
    m_pos(std::move(src.m_pos)), m_size(std::move(src.m_size)), m_text(std::move(src.m_text)), m_isHovering(false){
    Log::info("Button move");
    
}

Button& Button::operator=(const Button&& other) noexcept{
    Log::info("Button Move Operator");
    m_fontSize = other.m_fontSize;
    m_isHovering = other.m_isHovering;
    m_pos = other.m_pos;
    m_text = other.m_text;
    m_visible = other.m_visible;

    return *this;
}


Button::~Button(){
    Log::info("Button dstr");
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
            onClick.emit();
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