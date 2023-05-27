#ifndef _UiButton
#define _UiButton

#include <string>

#include "raylib.h"

class UiButton{
public:
    virtual ~UiButton(){}
    virtual const Vector2& getSize() const = 0;
    virtual const Vector2& getPos() const = 0;
    virtual void setPos(Vector2 pos) = 0;
    virtual void handleInput() = 0;
    virtual void render() const = 0;
    virtual void setText(const std::string& text) = 0;
    virtual const std::string& getText() const = 0;

    void setPos(float x, float y){
        setPos(Vector2{x,y});
    }
    void setVisible(bool visible){m_visible = visible;}
    const bool isVisible() const {return m_visible;}
    
protected:
    bool m_visible = true;

private:
    
};

#endif
