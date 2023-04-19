#ifndef _UiElement
#define _UiElement

#include "raylib.h"

class UiElement{
public:
    virtual ~UiElement(){}
    virtual const Vector2& getSize() const = 0;
    virtual const Vector2& getPos() const = 0;
    virtual void onHover(bool isHovering) = 0;
    virtual void onMouseReleased() = 0;
    virtual void render() const = 0;

private:

};

#endif
