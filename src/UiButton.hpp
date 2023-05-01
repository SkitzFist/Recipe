#ifndef _UiElement
#define _UiElement

#include "raylib.h"

class UiButton{
public:
    virtual ~UiButton(){}
    virtual const Vector2& getSize() const = 0;
    virtual const Vector2& getPos() const = 0;
    virtual void handleInput() = 0;
    virtual void render() const = 0;

private:

};

#endif
