#include "View.h"
#include "Lerp.hpp"

//Debug
#include "Log.hpp"

View::View(Vector2 outOfViewPos, Vector2 inViewPos, Vector2 size):
    m_size(size), m_currentPos(outOfViewPos), m_outOfViewPos(outOfViewPos), m_inViewPos(inViewPos),
    m_isVisible(false), m_transitionTimer(800), m_isInTransition(false), m_transitionShow(true){
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
