#include "View.h"
#include "Lerp.hpp"
#include "Settings.h"

View::View() :
    View(Vector2{0.f,0.f}, Vector2{0.0f,0.f}, Vector2{0.f,0.f}){
}

View::View(const Vector2& outOfViewPos, const Vector2& inViewPos, const Vector2& size):
    m_size(size), m_currentPos(outOfViewPos), m_outOfViewPos(outOfViewPos), m_inViewPos(inViewPos),
    m_isVisible(false), m_transitionTimer(Settings::VIEW_TRANSITION_DURATION_MS), m_isInTransition(false), m_transitionShow(true){
}

View::~View(){
}

void View::update(const float dt){
    if(!m_isInTransition){
        return;
    }

    if(m_transitionShow){
        transition(m_outOfViewPos, m_inViewPos, Lerp::easeOutBack);
    }else{
        
        transition( m_inViewPos, m_outOfViewPos, Lerp::easeOutBack);
    }

    if(m_transitionTimer.hasElapsed()){
        m_isVisible = m_transitionShow;
        m_isInTransition = false;
    }
}

void View::transition(Vector2 startPos, Vector2 endPos, const float(*lerpPtr)(float)){
        float time = lerpPtr(m_transitionTimer.getTime());
        float newX = Lerp::lerp(time, startPos.x, endPos.x);
        float newY = Lerp::lerp(time, startPos.y, endPos.y);
        m_currentPos = {newX, newY};
}

void View::toggleVisibility(){
    if(m_isVisible){
        hide();
    }else{
        show();
    }
}

void View::show(){
    m_transitionShow = true;
    m_isInTransition = true;

    m_transitionTimer.reset();
}

void View::hide(){
    m_transitionShow = false;
    m_isInTransition = true;

    m_transitionTimer.reset();
}

const bool View::isVisible() const{
    return m_isVisible;
}

void View::setVisible(bool visible){
    if(visible != m_isVisible)
        toggleVisibility();
}

const bool View::isInTransition() const{
    return m_isInTransition;
}


void View::setOutOfViewPos(Vector2 pos){
    m_outOfViewPos = pos;
}

void View::setInViewPos(Vector2 pos){
    m_inViewPos = pos;
}

void View::setSize(Vector2 size){
    m_size = size;
}