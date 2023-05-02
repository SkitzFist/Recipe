#include "StateAddRecipe.hpp"

#include "Settings.h"
#include "Button.hpp"

StateAddRecipe::StateAddRecipe(EventBus* eventBus):
    State(eventBus), EventHandler<PrepareAddRecipe>(getNewId()){

    Vector2 inputSize = {Settings::WIDTH * 0.75f, Settings::HEIGHT * 0.025};
    m_inputGroups.emplace_back(InputGroup("Name", new InputField(inputSize)));
    m_inputGroups.emplace_back(InputGroup("Reference", new InputField(inputSize)));
    m_inputGroups.emplace_back(InputGroup("Tags", new InputField(inputSize)));

    Vector2 buttonSize = {250, 50};
    Button<SwitchStateToMainMenu>* backButton = new Button<SwitchStateToMainMenu>(buttonSize, eventBus, "Back");
    Button<PrepareAddRecipe>* addRecipeButton = new Button<PrepareAddRecipe>(buttonSize, eventBus, "Add");


    m_buttons.emplace_back(backButton);
    m_buttons.emplace_back(addRecipeButton);

    eventBus->registerHandler<PrepareAddRecipe>(this);
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
                index = i;
                break;
            }
        }

        if(index == -1){
            m_inputGroups[0].inputField->onFocus();
        }else{
            m_inputGroups[index].inputField->onBlur();
            index = (index + 1) % (m_inputGroups.size());
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

void StateAddRecipe::onEvent(const PrepareAddRecipe& event){
    std::vector<std::string> dataBaseEntry;
    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        std::string str = m_inputGroups[i].inputField->getText();
        
        if(!validEntry(str)){
            log("Not valid entry: " + m_inputGroups[i].text);
            return;
        }
        dataBaseEntry.emplace_back(str);
    }

    for(int i = 0; i < dataBaseEntry.size(); ++i){
        log(std::to_string(i) + ": " + dataBaseEntry[i]);
    }

    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        m_inputGroups[i].inputField->clear();
    }

    m_eventBus->fireEvent(AddRecipe(dataBaseEntry));
}

const bool StateAddRecipe::validEntry(const std::string& str) const{
    if(str.empty()){
        return false;
    }

    if(!(str.find_first_not_of(' ') != std::string::npos)){
        return false;
    }

    return true;
}
