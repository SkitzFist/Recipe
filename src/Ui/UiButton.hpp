#ifndef _UiElement
#define _UiElement

#include "raylib.h"

class UiButton{
public:
    virtual ~UiButton(){}
    virtual const Vector2& getSize() const = 0;
    virtual const Vector2& getPos() const = 0;
    virtual void setPos(Vector2 pos) = 0;
    void setPos(float x, float y){
        setPos(Vector2{x,y});
    }
    virtual void handleInput() = 0;
    virtual void render() const = 0;
    void setVisible(bool visible){m_visible = visible;}
    const bool isVisible() const {return m_visible;}

protected:
    bool m_visible = true;

private:
    
};

#endif
