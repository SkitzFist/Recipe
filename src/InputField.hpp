#ifndef _InputField
#define _InputField

#include <string>

#include "raylib.h"

typedef struct Vector2i{ //todo, move this
    int x;
    int y;
}Vector2i;

struct TextMarkerBox{
    Vector2 pos;
    Vector2 size;
};

class InputField{
public:
    InputField(Vector2 size);
    ~InputField();
    void handleInput();
    void update(float dt);
    void render() const;

    void onFocus();
    const bool isFocused() const;
    void onBlur();

    const Vector2 getPos() const;
    void setPos(Vector2 pos);
    const Vector2 getSize() const;

    const std::string& getText();
    void clear();

private:
    Vector2 m_pos;
    Vector2 m_size;
    bool m_isFocused;

    std::string m_text;
    int m_fontSize;
    void handleTextInput();
    Vector2 getTextPos() const;
    
    const float BLINK_TIME;
    float m_blinkTimer;
    bool m_carrotVisible;
    int m_carrotPos;
    void updateCarrot(float dt);
    void removeCarrot();
    void placeCarrotAt(int index);
    void handleCarrotOffset();
    const bool canMoveCarrot(int offset) const;

    const float REMOVAL_COOLDOWN_START;
    float m_removalTimer;
    bool m_removalInProgress;
    float m_removalElapsed;
    bool canRemoveBackwards()const;
    void handleRemoveBackward();

    bool m_markTextInProgress;
    Vector2 m_markTextStartPos;
    Vector2i m_markTextIndexes;
    TextMarkerBox m_textMarkerBox;
    void handleMarkText();
    void clearMarkText();

};

#endif