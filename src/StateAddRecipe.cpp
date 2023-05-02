#include "StateAddRecipe.hpp"

#include "Settings.h"
#include "Button.hpp"

StateAddRecipe::StateAddRecipe(EventBus* eventBus):
    State(eventBus){

    Vector2 inputSize = {Settings::WIDTH * 0.75f, Settings::HEIGHT * 0.025};
    m_inputGroups.emplace_back(InputGroup("Name", new InputField(inputSize)));
    m_inputGroups.emplace_back(InputGroup("Reference", new InputField(inputSize)));
    m_inputGroups.emplace_back(InputGroup("Tags", new InputField(inputSize)));

    Vector2 buttonSize = {250, 50};
    Button<SwitchStateToMainMenu>* backButton = new Button<SwitchStateToMainMenu>(buttonSize, eventBus, "Back");
    Button<PrepareAddRecipe>* addRecipeButton = new Button<PrepareAddRecipe>(buttonSize, eventBus, "Add");


    m_buttons.emplace_back(backButton);
    m_buttons.emplace_back(addRecipeButton);
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

    if(IsKeyPressed(KEY_TAB)){
        int index = -1;
        for(int i = 0; i < m_inputGroups.size(); ++i){
            if(m_inputGroups[i].inputField->isFocused()){
                log("focused");
                index = i;
                log("index: " + std::to_string(index));
                break;
            }
        }

        if(index == -1){
            m_inputGroups[0].inputField->onFocus();
        }else{
            m_inputGroups[index].inputField->onBlur();
            index = (index + 1) % (m_inputGroups.size());
            log("index %: " + std::to_string(index));
            m_inputGroups[index].inputField->onFocus();
        }
       
    }
}

void StateAddRecipe::update(float dt){
    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        m_inputGroups[i].inputField->update(dt);
    }
}

void StateAddRecipe::render() const{
    float nextYPos = m_inputGroups[0].inputField->getSize().y * 4.f;
    float xPos = m_inputGroups[0].inputField->getSize().x / 14.f;

    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        InputField* inputField = m_inputGroups[i].inputField;
        int fontSize = GetFontDefault().baseSize * 4;
        Vector2 textSize = MeasureTextEx(GetFontDefault(), m_inputGroups[i].text.c_str(), (GetFontDefault().baseSize * 4), 2.f);
        
        Vector2 textPos{ xPos, nextYPos};
        Vector2 inputPos{xPos, textPos.y + (textSize.y * 1.1f)};
        inputField->setPos(inputPos);
        
        DrawTextEx(GetFontDefault(), m_inputGroups[i].text.c_str(), textPos, fontSize, 2.f, DARKGRAY);
        inputField->render();

        nextYPos = inputPos.y + (inputField->getSize().y * 2.f);
    }

    nextYPos *= 2.f;
    
    float buttonSpacing = m_buttons[0]->getSize().x * 0.25f;
    for(UiButton* button : m_buttons){
        button->setPos(xPos, nextYPos);    
        button->render();
        xPos += button->getSize().x + buttonSpacing;
    }
}
