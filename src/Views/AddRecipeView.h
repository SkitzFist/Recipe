#ifndef _AddRecipeView
#define _AddRecipeView

#include <vector>
#include <memory>

#include "View.h"

#include "Settings.h"
#include "Ui/InputField.hpp"

////////////////////////////////////////////////////////////////////////////////////
///Size & Positions
inline constexpr Vector2 size = {Settings::WIDTH * 0.8f, Settings::HEIGHT * 0.8f};
inline constexpr Vector2 inViewPos {
    Settings::X_ALIGNMENT,
    (Settings::HEIGHT / 2.f) - (size.y / 2.f)
};
inline constexpr Vector2 outOfViewPos{
    0 - size.x - 10.f,
    inViewPos.y
};
////////////////////////////////////////////////////////////////////////////////

struct InputGroup{
    std::unique_ptr<InputField> inputField;
    std::string title;
    
    InputGroup(std::unique_ptr<InputField> _inputField, std::string _title): 
        inputField(std::move(_inputField)), title(_title){}

};

class AddRecipeView : public View{
public:
    AddRecipeView(EventBus* eventBus);
    virtual ~AddRecipeView();

    virtual void handleInput() override;
    virtual void update(const float dt) override;
    virtual void render() const override;

private:
    std::vector<InputGroup> m_inputGroups;
    float m_localXAlignment;
};

#endif