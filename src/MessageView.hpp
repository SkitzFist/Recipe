#ifndef _MessageView
#define _MessageView

#include "View.h"

#include <vector>

#include "Ui/UiButton.hpp"
#include "Vector2i.hpp"

class MessageView : public View{
public:
    MessageView(int id, const std::string& title, const std::string& text, const std::string& buttonText = "Close");
    virtual ~MessageView() override;
    
    //_____________________________________///
    //       inherited from View          ///
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;
    //_________________________________///

    const int getId() const;

    Signal<int> onClick;
private:
    int m_id;
    std::string m_title;
    Vector2 m_titlePos;

    std::string m_text;
    float m_fontSize;
    Vector2 m_textPos;

    UiButton* m_button;
    std::string m_buttonText;
    const Vector2 getSizeOfChildElements() const;

    const float getNextHalfPointY(Vector2 a, Vector2 size) const;
    void updatePositions();
};

#endif