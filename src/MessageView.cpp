#include "MessageView.hpp"

#include <cmath>

#include "Settings.h"
#include "Text/FitTextByWidth.hpp"
#include "Ui/Button.hpp"
#include "Lerp.hpp"

MessageView::MessageView(int id, const std::string& title, const std::string& text, const std::string& buttonText):
    m_id(id), m_title(title), m_text(text), m_buttonText(buttonText){

    m_fontSize = Settings::FONT_SIZE / 2.f;

    m_text = TextUtility::fitTextByWidth(m_text, m_fontSize, Settings::MESSAGE_VIEW_MAX_WIDTH);

    Vector2 buttonTextSize = MeasureTextEx(GetFontDefault(), m_buttonText.c_str(), m_fontSize, 2.f);
    m_button = new Button({0.f,0.f}, Vector2{buttonTextSize.x * 2.f, buttonTextSize.y * 2.f} , m_buttonText);

    //connect button signal with messageController signal. 
    MessageView* ptr = this;
    m_button->onClick.connect([ptr](){
        ptr->hide();
        ptr->onClick.emit(ptr->getId());
    });

    //Set size of panel
    Vector2 sizeOfChildElements = getSizeOfChildElements();
    m_size = {sizeOfChildElements.x * 1.2f, sizeOfChildElements.y * 2.f};

    //set positions
    Vector2 outOfViewPos = {
        (Settings::WIDTH / 2.f) - (m_size.x / 2.f),
        0 - m_size.y
    };
    setOutOfViewPos(outOfViewPos);  
    m_currentPos = outOfViewPos;

    Vector2 inViewPos = {
        outOfViewPos.x,
        (Settings::HEIGHT/2.f) - (m_size.y / 2.f)
    };
    setInViewPos(inViewPos);

    //init transition animation
    show();
}

MessageView::~MessageView(){
    delete m_button;
}

void MessageView::handleInput(){
    m_button->handleInput();
}



void MessageView::update(float dt){
    View::update(dt);

    updatePositions();
}

void MessageView::updatePositions(){
    Vector2 titleSize = MeasureTextEx(GetFontDefault(), m_title.c_str(), Settings::FONT_SIZE, 2.f);
    float halfPointX = m_currentPos.x + (m_size.x / 2.f);
    m_titlePos = {
        halfPointX - (titleSize.x / 2.f),
        m_currentPos.y + (titleSize.y /2.f)
    };

    Vector2 textSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, 2.f);
    float halfPointY = getNextHalfPointY(m_titlePos, titleSize) - m_button->getSize().y;
    m_textPos = {
        halfPointX - (textSize.x / 2.f),
        halfPointY
    };

    halfPointY = getNextHalfPointY(m_textPos, textSize);
    Vector2 buttonPos = {
        halfPointX - (m_button->getSize().x/2.f),
        halfPointY - (m_button->getSize().y / 2.f)
    };
    m_button->setPos(buttonPos);
}

const float MessageView::getNextHalfPointY(Vector2 a, Vector2 size) const{
    float posAY = a.y + size.y;
    float posBY = m_currentPos.y + m_size.y;
    return Lerp::lerp(0.5f, posAY, posBY);
}

void MessageView::render() const{
    //draw panel
    float roundness = 0.5f;
    int segments = 64;

    Rectangle rec = {
            m_currentPos.x,
            m_currentPos.y,
            m_size.x,
            m_size.y
    };
    Rectangle borderRec;
    borderRec.width = rec.width * 1.02f;
    borderRec.height = rec.height * 1.05f;
    borderRec.x = m_currentPos.x + (rec.width / 2.f) - (borderRec.width / 2.f);
    borderRec.y = m_currentPos.y + (rec.height / 2.f) - (borderRec.height / 2.f);
    DrawRectangleRounded(borderRec, roundness, segments, BLACK);

    BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);
        DrawRectangleRounded(rec, roundness, segments, Settings::MESSAGE_VIEW_BGR_COLOR);
    EndBlendMode();
    

    float spacing = 2.f;
    //draw title
    DrawTextEx(GetFontDefault(), m_title.c_str(), m_titlePos, Settings::FONT_SIZE, spacing, Settings::BUTTON_TEXT_COLOR);

    //draw text
    DrawTextEx( GetFontDefault(), m_text.c_str(), m_textPos, m_fontSize, spacing, Settings::BUTTON_TEXT_COLOR);

    m_button->render();
}

const int MessageView::getId() const{
    return m_id;
}

const Vector2 MessageView::getSizeOfChildElements() const{
    float spacing = 2.f;

    //init with text side as it's width is the total width.
    Vector2 size = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_fontSize, spacing);
    
    Vector2 titleSize = MeasureTextEx(GetFontDefault(), m_title.c_str(), Settings::FONT_SIZE, spacing);
    size.y += titleSize.y;

    Vector2 buttonSize = m_button->getSize();
    size.y += buttonSize.y;

    return size;
}