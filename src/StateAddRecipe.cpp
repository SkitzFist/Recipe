
/*
#include "StateAddRecipe.hpp"

#include <stdlib.h>

#include "Settings.h"
#include "Button.hpp"

StateAddRecipe::StateAddRecipe(EventBus* eventBus):
    State(eventBus), EventHandler<PrepareAddRecipeEvent>(getNewId()), EventHandler<PrepareModifyRecipeEvent>(getNewId()),
    EventHandler<ClearInputEvent>(getNewId()), EventHandler<SearchFoundEvent>(getNewId()){

    Vector2 inputSize = {Settings::WIDTH * 0.75f, Settings::HEIGHT * 0.025};
    m_inputGroups.emplace_back(std::make_unique<InputGroup>("Search", std::make_unique<InputField>(Vector2{inputSize.x / 2.f, inputSize.y}, eventBus)));
    m_inputGroups.emplace_back(std::make_unique<InputGroup>("Name", std::make_unique<InputField>(inputSize, eventBus)));
    m_inputGroups.emplace_back(std::make_unique<InputGroup>("Reference", std::make_unique<InputField>(inputSize, eventBus)));
    m_inputGroups.emplace_back(std::make_unique<InputGroup>("Tags", std::make_unique<InputField>(inputSize, eventBus)));

    for(int i = 1; i < m_inputGroups.size(); ++i){
            m_inputGroups[i]->inputField->setEvent(new PrepareAddRecipeEvent());
    }

    int nrOfButtons = 3;
    Vector2 buttonSize = { 0.f, inputSize.y * 2.f};
    float buttonSizeX = (inputSize.x / nrOfButtons);
    m_buttonSpacing = 0.05f * inputSize.x;
    buttonSizeX -= m_buttonSpacing;
    buttonSize.x = buttonSizeX;     

    m_addRecipeButton = new Button<PrepareAddRecipeEvent>(buttonSize, eventBus, "Add");
    m_modifyRecipeButton = new Button<PrepareModifyRecipeEvent>(buttonSize, eventBus, "Modify");
    m_modifyRecipeButton->setVisible(false);
    m_clearButton = new Button<ClearInputEvent>(buttonSize, eventBus, "Clear");
    

    eventBus->registerHandler<PrepareAddRecipeEvent>(this);
    eventBus->registerHandler<PrepareModifyRecipeEvent>(this);
    eventBus->registerHandler<ClearInputEvent>(this);
    eventBus->registerHandler<SearchFoundEvent>(this);
}

StateAddRecipe::~StateAddRecipe(){
    delete m_backButton;
    delete m_addRecipeButton;
    delete m_modifyRecipeButton;
    delete m_clearButton;
}

void StateAddRecipe::handleInput(){
    handleTab();
    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        m_inputGroups[i]->inputField->handleInput();
    }

    m_addRecipeButton->handleInput();
    m_backButton->handleInput();
    m_modifyRecipeButton->handleInput();
    m_clearButton->handleInput();

    if(IsKeyPressed(KEY_ENTER)){
        if(m_inputGroups[0]->isFocused()){
            handlePrepareSearchRecipeEvent();
        }else if(m_inputGroups[1]->isFocused() || m_inputGroups[2]->isFocused() || m_inputGroups[3]->isFocused()){
            if(m_addRecipeButton->isVisible()){
                handlePrepareAddRecipeEvent();
            }else{
                handlePrepareModifyRecipeEvent();
            }
        }
    }
}

void StateAddRecipe::handleTab(){
    bool isReverseTab = IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_TAB);
    if(isReverseTab){
        int prevIndex = -1;
        for(int i = 0; i < m_inputGroups.size(); ++i){
            if(m_inputGroups[i]->inputField->isFocused()){
                prevIndex = i;
                break;
            }
        }

        if(prevIndex == -1){
            m_inputGroups[m_inputGroups.size() -1]->inputField->onFocus();
            return;
        }

        int index = ((prevIndex) - 1 < 0 ? m_inputGroups.size() -1 : abs(prevIndex - 1));
        m_inputGroups[prevIndex]->inputField->onBlur();
        m_inputGroups[index]->inputField->onFocus();
        
    }else if(IsKeyPressed(KEY_TAB) && !isReverseTab){
        int index = -1;
        for(int i = 0; i < m_inputGroups.size(); ++i){
            if(m_inputGroups[i]->inputField->isFocused()){
                index = i;
                break;
            }
        }

        if(index == -1){
            m_inputGroups[0]->inputField->onFocus();
        }else{
            m_inputGroups[index]->inputField->onBlur();
            index = (index + 1) % (m_inputGroups.size());
            m_inputGroups[index]->inputField->onFocus();
        }
    }
}

void StateAddRecipe::update(float dt){
    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        m_inputGroups[i]->inputField->update(dt);
    }
}

void StateAddRecipe::toggleState(){
    m_addRecipeButton->setVisible(!m_addRecipeButton->isVisible());
    m_modifyRecipeButton->setVisible(!m_addRecipeButton->isVisible());
}

void StateAddRecipe::render() const{
    float nextYPos = m_inputGroups[0]->inputField->getSize().y * 8.f;
    float xPos = m_inputGroups[0]->inputField->getSize().x / 14.f;

    for(std::size_t i = 0; i < m_inputGroups.size(); ++i){
        int fontSize = GetFontDefault().baseSize * 4;
        Vector2 textSize = MeasureTextEx(GetFontDefault(), m_inputGroups[i]->text.c_str(), (GetFontDefault().baseSize * 4), 2.f);
        
        Vector2 textPos{ xPos, nextYPos};
        Vector2 inputPos{xPos, textPos.y + (textSize.y * 1.1f)};
        m_inputGroups[i]->inputField->setPos(inputPos);
        
        DrawTextEx(GetFontDefault(), m_inputGroups[i]->text.c_str(), textPos, fontSize, 2.f, INPUT_TITLE_COLOR);
        m_inputGroups[i]->inputField->render();

        nextYPos = inputPos.y + (m_inputGroups[i]->inputField->getSize().y * 2.f);
        if(i == 0)
            nextYPos *= 1.2f;
    }

    m_backButton->setPos(xPos, nextYPos);
    m_backButton->render();
    xPos += m_backButton->getSize().x + m_buttonSpacing;

    UiButton* button = m_addRecipeButton->isVisible() ? m_addRecipeButton : m_modifyRecipeButton;
    button->setPos(xPos, nextYPos);
    button->render();

    xPos += button->getSize().x + m_buttonSpacing;

    m_clearButton->setPos(xPos, nextYPos);
    m_clearButton->render();
}

const int StateAddRecipe::getInputIndex(const std::string& groupName) const{
    for(int i = 0 ; i < m_inputGroups.size(); ++i){
        if(m_inputGroups[i]->text == groupName){
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////// EVENT HANDLERS ////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const bool StateAddRecipe::inputFieldsAreValid() const{
    int nameInputIndex = getInputIndex("Name");
    int referenceInputIndex = getInputIndex("Reference");
    int tagsInputIndex = getInputIndex("Tags");

    bool isValidIndexes = (
        nameInputIndex != -1 ||
        referenceInputIndex != -1 ||
        tagsInputIndex != -1
    );

    if(!isValidIndexes)
        return false;
    
    bool isValidInputs = (
        isValidEntry(m_inputGroups[nameInputIndex]->text) ||
        isValidEntry(m_inputGroups[referenceInputIndex]->text) ||
        isValidEntry(m_inputGroups[tagsInputIndex]->text)
    );

    if(!isValidInputs)
        return false;

    return true;
}

////////////////////////////
///PrepareAddRecipeEvent///
//////////////////////////
void StateAddRecipe::onEvent(const PrepareAddRecipeEvent& event){
    handlePrepareAddRecipeEvent();
}

void StateAddRecipe::handlePrepareAddRecipeEvent(){
        if(inputFieldsAreValid()){
        int nameInputIndex = getInputIndex("Name");
        Recipe recipe;
        recipe.name = m_inputGroups[nameInputIndex]->inputField->getText();
        recipe.reference = m_inputGroups[nameInputIndex + 1]->inputField->getText();
        recipe.tags = m_inputGroups[nameInputIndex + 2]->inputField->getText(); // TODO: need to verify tags

        handleClearInputEvent();
        m_eventBus->fireEvent(AddRecipeEvent(recipe));
    }
}

///////////////////////////////
///PrepareModifyRecipeEvent///
/////////////////////////////
void StateAddRecipe::onEvent(const PrepareModifyRecipeEvent& event){
    handlePrepareModifyRecipeEvent();
}

void StateAddRecipe::handlePrepareModifyRecipeEvent(){
         if(inputFieldsAreValid()){
        int nameInputIndex = getInputIndex("Name");
        Recipe recipe;
        recipe.name = m_inputGroups[nameInputIndex]->inputField->getText();
        recipe.reference = m_inputGroups[nameInputIndex + 1]->inputField->getText();
        recipe.tags = m_inputGroups[nameInputIndex + 2]->inputField->getText(); // TODO: need to verify tags

        handleClearInputEvent();
        m_eventBus->fireEvent(ModifyRecipeEvent(recipe));
    }    
}

//////////////////////
///ClearInputEvent///
////////////////////
void StateAddRecipe::onEvent(const ClearInputEvent& event){
    handleClearInputEvent();
}

void StateAddRecipe::handleClearInputEvent(){
    for(int i = 0; i < m_inputGroups.size(); ++i){
        m_inputGroups[i]->inputField->clear();
    }

    if(m_modifyRecipeButton->isVisible()){
        toggleState();
    }
}

//////////////////////////////
///PrepareSarchRecipeEvent///
////////////////////////////
void StateAddRecipe::handlePrepareSearchRecipeEvent(){
    int inputIndex = getInputIndex("Search");
    if(inputIndex == -1)
        return;
    
    std::string recipeName = m_inputGroups[inputIndex]->inputField->getText();
    if(!isValidEntry(recipeName)){
        return;
    }

    Log::info("Prepare to search for: " + recipeName);
    m_eventBus->fireEvent(SearchRecipeEvent(recipeName));
}

const bool StateAddRecipe::isValidEntry(const std::string& str) const{
    if(str.empty()){
        return false;
    }

    if(!(str.find_first_not_of(' ') != std::string::npos)){
        return false;
    }

    return true;
}

///////////////////////
///SearchFoundEvent///
    /////////////////////

void StateAddRecipe::onEvent(const SearchFoundEvent& event){
    int nameInputIndex = getInputIndex("Name");

    m_inputGroups[nameInputIndex]->inputField->setText(event.recipe.name);
    m_inputGroups[nameInputIndex + 1]->inputField->setText(event.recipe.reference);
    m_inputGroups[nameInputIndex + 2]->inputField->setText(event.recipe.tags);
    
    toggleState();
}
*/