#include "AddRecipeView.h"

#include "Settings.h"
#include "Ui/Button.hpp"
#include "Recipe.hpp"

//debug
#include "Log.hpp"

AddRecipeView::AddRecipeView(const Vector2& outOfViewPos, const Vector2& inViewPos):
View(outOfViewPos, inViewPos, Settings::BIG_PANEL_SIZE), m_inputGroups(3){

    Vector2 inputFieldSize = {
        Settings::BIG_PANEL_SIZE.x * 0.9f,
        Settings::BIG_PANEL_SIZE.y * 0.05
    };

    m_localXAlignment = (Settings::BIG_PANEL_SIZE.x / 2.f) - (inputFieldSize.x / 2.f);

    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Name"
    ));

    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Reference"
    ));
    
    m_inputGroups.add(new InputGroup(
        new InputField(inputFieldSize),
        "Tags"
    ));
    
    AddRecipeView* ptr = this;
    for(InputGroup* group : m_inputGroups){
        group->inputField->onSubmit.connect([ptr](){
            ptr->onAddRecipe();
        });
        m_tabCycling.addInputField(group->inputField);
    }

    m_addButton = new Button(m_currentPos, Vector2{inputFieldSize.x / 2.f,50}, "Add");
}

AddRecipeView::~AddRecipeView(){
    m_inputGroups.clear();
    delete m_addButton;
}

void AddRecipeView::handleInput(){

    if(!isVisible()){
        return;
    }

    m_tabCycling.handleInput();

    for(InputGroup* group : m_inputGroups){
        group->inputField->handleInput();
    }

    m_addButton->handleInput();
}

void AddRecipeView::update(const float dt){
    View::update(dt);

    for(InputGroup* group : m_inputGroups){
        group->inputField->update(dt);
    }
}

void AddRecipeView::render() const{
    BeginBlendMode(BLEND_ADDITIVE);
        DrawRectangle(m_currentPos.x, m_currentPos.y, Settings::BIG_PANEL_SIZE.x, 
        Settings::BIG_PANEL_SIZE.y, Settings::VIEW_BACKGROUND_COLOR);  
    EndBlendMode();

    int titleFontSize = GetFontDefault().baseSize * 5;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), "Add Recipe", titleFontSize, 2.f);
    Vector2 titlePos = {
        m_currentPos.x + (m_size.x / 2.f) - (textSize.x / 2.f),
        m_currentPos.y + (m_size.y * 0.05f)
    };
    DrawText("Add Recipe", titlePos.x, titlePos.y, titleFontSize, Settings::BUTTON_TEXT_COLOR);
    
    float nextYPos = m_size.y * 0.3f;
    for(const InputGroup* group : m_inputGroups){
        float fontSize = GetFontDefault().baseSize * 4.f;
        DrawTextEx(GetFontDefault(), group->title.c_str(), {m_currentPos.x + m_localXAlignment, nextYPos}, fontSize, 2.f, Settings::BUTTON_TEXT_COLOR);
        Vector2 textSize = MeasureTextEx(GetFontDefault(), group->title.c_str(), fontSize, 2.f);
        nextYPos += textSize.y * 1.2f;
        group->inputField->setPos({m_currentPos.x + m_localXAlignment, nextYPos});
        nextYPos += group->inputField->getSize().y + textSize.y;
        group->inputField->render();
    }

    float buttonSpacing = m_size.y * 0.05f;
    m_addButton->setPos(
        m_currentPos.x + (m_addButton->getSize().x / 2.f),
        m_currentPos.y + nextYPos + buttonSpacing
    ),
    m_addButton->render();
}

void AddRecipeView::onAddRecipe(){
    if (!allInputFieldHasValidInput())
    {
        // TODO add messageView
        return;
    }

    Recipe recipe;
    recipe.name = m_inputGroups[0]->inputField->getText();
    recipe.reference = m_inputGroups[1]->inputField->getText();
    recipe.tags = m_inputGroups[2]->inputField->getText();

    for (InputGroup *group : m_inputGroups)
    {
        group->inputField->clear();
    }
}

bool AddRecipeView::allInputFieldHasValidInput()
{
    for (InputGroup *group : m_inputGroups)
    {
        std::string text = group->inputField->getText();
        if (text.empty() || (!(text.find_first_not_of(' ') != std::string::npos)))
        {
            return false;
        }
    }
    return true;
}
