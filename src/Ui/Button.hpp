#ifndef _Button
#define _Button

#include "Ui/UiButton.hpp"

#include "Settings.h"
#include "Collision.h"

class Button : public UiButton{

public:

    Button(Vector2 pos, Vector2 size, const std::string& text);
    Button(Button&& src) noexcept;
    
    virtual ~Button() override;

    Button& operator=(const Button&& other) noexcept;

    ///////////////////////////////////////////////////
    ////////   Inherited from UiButton
    virtual const Vector2& getSize() const override;
    virtual const Vector2& getPos() const override;
    virtual void setPos(Vector2 pos) override;
    virtual void handleInput() override;
    virtual void render() const override;
    virtual void setText(const std::string& text) override;
    virtual const std::string& getText() const override;
    /////////////////////////////////////////////////

private:
    Vector2 m_pos;
    Vector2 m_size;

    std::string m_text;
    int m_fontSize;
    bool m_isHovering;
};

#endif