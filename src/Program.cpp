#include "Program.h"

#include "Settings.h"
#include "raylib.h"

#include "Views/AddRecipeView.h"
#include "Ui/ExpandingButton.hpp"

Program::Program(EventBus* eventBus) : 
    EventHandler<ToggelAddRecipeViewEvent>(getNewId()){
    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetWindowPosition(GetScreenWidth(), 25.f);
    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    
    Vector2 viewButtonSize = {50, 50};
    Vector2 viewButtonPos = {20.f, Settings::HEIGHT / 2.f};
    m_viewGroups.emplace_back(
        std::make_unique<AddRecipeView>(),
        std::make_unique<ExpandingButton<ToggelAddRecipeViewEvent>>(viewButtonSize, eventBus, "Add recipe", viewButtonPos),
        ADD_STATE
    );

    eventBus->registerHandler<ToggelAddRecipeViewEvent>(this);
}

Program::~Program(){
}

void Program::run(){
    while (!WindowShouldClose())
    {
        float dt = m_frameTimer.getElapsed();
        m_frameTimer.reset();
        handleInput();
        update(dt);    
        render();
    }
    CloseWindow();
}

void Program::handleInput(){
    for(ViewGroup& group : m_viewGroups){
        if(group.view->isVisible() || group.view->isInTransition()){
            group.view->handleInput();
        }

        if(!group.view->isInTransition()){
            group.button->handleInput();
        }
    }      
}

void Program::update(float dt){
    for(ViewGroup& group : m_viewGroups){
        if(group.view->isVisible() || group.view->isInTransition()){
            group.view->update(dt);
        }
    }   
}

void Program::render() const{
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
        for(const ViewGroup& group : m_viewGroups){
            if(group.view->isVisible() || group.view->isInTransition()){
                group.view->render();
            }
            
            group.button->render();
        }     
    EndDrawing();
}

const int Program::getViewGroupIndex(ViewType type) const{
    for(int i = 0; i < m_viewGroups.size(); ++i){
        if(m_viewGroups[i].type == type){
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////////////////////////////
///                  EVENTS                               ///
////////////////////////////////////////////////////////////
void Program::onEvent(const ToggelAddRecipeViewEvent& event){
    m_viewGroups[0].view->toggleVisibility();
}

