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
    View();

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

    float m_localXAlignment;
protected:
    Vector2 m_size;
    Vector2 m_currentPos;
    
    Vector2 m_outOfViewPos;
    Vector2 m_inViewPos;
    void setOutOfViewPos(Vector2 pos);
    void setInViewPos(Vector2 pos);
    void setSize(Vector2 size);

public:    
    class InputGroup{
    public:
        InputField* inputField;
        std::string title;

        InputGroup(InputField* _inputField, const std::string& _title):
            inputField(_inputField), title(_title){}

        InputGroup(InputGroup&& src) noexcept :
            inputField(std::move(src.inputField)), title(std::move(src.title)){
        }

        ~InputGroup(){
            delete inputField;
        }

    };

private:


    bool m_isVisible;

    Timer m_transitionTimer;
    bool m_isInTransition;
    bool m_transitionShow;
    void transition(Vector2 startPos, Vector2 endPos, const float(*lerpPtr)(float));
};

#endif