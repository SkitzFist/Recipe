#include "StateAddRecipe.hpp"

#include "Settings.h"
#include "Button.hpp"

StateAddRecipe::StateAddRecipe(EventBus* eventBus):
    State(eventBus){

    Vector2 inputSize = {700.f, 25.f};
    m_inputGroups.emplace_back(InputGroup("Namn", new InputField(inputSize)));
    m_inputGroups.emplace_back(InputGroup("Referens", new InputField(inputSize)));
    m_inputGroups.emplace_back(InputGroup("Taggar", new InputField(inputSize)));

    Vector2 buttonSize = {250, 50};
    Button<SwitchStateToMainMenu>* backButton = new Button<SwitchStateToMainMenu>(buttonSize, eventBus, "Back");
    Button<AddRecipe>* AddRecipeButton = new Button<AddRecipe>(buttonSize, eventBus, "Lägg till");
    log(GetWorkingDirectory());
}

StateAddRecipe::~StateAddRecipe(){
    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        delete m_inputGroups[i].inputField;
    }

    for(std::size_t i = 0; i < m_buttons.size(); ++i){
            delete m_buttons[i];
    }
}

void StateAddRecipe::handleInput(){
    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        m_inputGroups[i].inputField->handleInput();
    }

    for(UiButton* button : m_buttons){
        button->handleInput();
    }
}

void StateAddRecipe::update(float dt){
    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){

        m_inputGroups[i].inputField->update(dt);
    }
}

void StateAddRecipe::render() const{
    float nameSpacing = 5.f;
    float nextYPos = 100.f;
    float xPos = 50.f;
    float groupSpacing = 20.f;

    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        InputField* inputField = m_inputGroups[i].inputField;
        int fontSize = GetFontDefault().baseSize * 4;
        Vector2 textSize = MeasureTextEx(GetFontDefault(), m_inputGroups[i].text.c_str(), (GetFontDefault().baseSize * 4), 2.f);
        
        Vector2 textPos{ xPos, nextYPos};
        Vector2 inputPos{xPos, textPos.y + textSize.y + nameSpacing};
        inputField->setPos(inputPos);
        
        DrawTextEx(GetFontDefault(), m_inputGroups[i].text.c_str(), textPos, fontSize, 2.f, DARKGRAY);
        inputField->render();

        nextYPos = inputPos.y + inputField->getSize().y + groupSpacing;
    }

    for(UiButton* button : m_buttons){
        button->render();
    }
}
