#ifndef _View
#define _View

#include "Timer.hpp"
#include "raylib.h"
#include "Ui/InputField.hpp"

class View{
public:
    class OnTransitionEndCallback{
        virtual void onTransitionEnd() = 0;
    };

public:
    View(const Vector2& outOfViewPos, const Vector2& inViewPos, const Vector2& size);
    virtual ~View();

    virtual void handleInput() = 0;
    virtual void update(const float dt);
    virtual void render() const = 0;

    void toggleVisibility();
    void show();
    void hide();
    const bool isVisible() const;
    void setVisible(bool visible);

    const bool isInTransition() const;
protected:
    Vector2 m_size;
    Vector2 m_currentPos;

protected:    
    struct InputGroup{
        InputField* inputField;
        std::string title;

        InputGroup(InputField* _inputField, const std::string& _title):
            inputField(_inputField), title(_title)
        {}

        ~InputGroup(){
            delete inputField;
        }

    };
private:
    Vector2 m_outOfViewPos;
    Vector2 m_inViewPos;

    bool m_isVisible;

    Timer m_transitionTimer;
    bool m_isInTransition;
    bool m_transitionShow;
    void transition(Vector2 startPos, Vector2 endPos, const float(*lerpPtr)(float));
};

#endif