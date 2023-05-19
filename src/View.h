#ifndef _View
#define _View

#include "Timer.hpp"
#include "raylib.h"


class View{
public:
    View(Vector2 outOfViewPos, Vector2 inViewPos, Vector2 size);
    virtual ~View();

    //virtual void handleInput() = 0;
    virtual void update(const float dt);
    virtual void render() const;

    void show();
    void hide();

    const bool isVisible() const;

private:
    Vector2 m_outOfViewPos;
    Vector2 m_inViewPos;
    Vector2 m_currentPos;

    Vector2 m_size;

    bool m_isVisible;

    Timer m_transitionTimer;
    bool m_isInTransition;
    bool m_transitionShow;
    bool m_transitionFinished;
    void transition(Vector2 startPos, Vector2 endPos, const float(*lerpPtr)(float));
};

#endif