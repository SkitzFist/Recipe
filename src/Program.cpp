#include "Program.h"

#include "Settings.h"
#include "raylib.h"

#include "Views/AddRecipeView.h"
#include "Views/ModifyRecipeView.h"

#include "Ui/ExpandingButton.hpp"


Program::Program(){
    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetWindowPosition(GetScreenWidth(), 25.f);
    SetTargetFPS(144);
    SetExitKey(KEY_ESCAPE);
    
    Vector2 inViewPos = {
        Settings::VIEW_X_ALIGNMENT,(Settings::HEIGHT / 2.f) - (Settings::BIG_PANEL_SIZE.y / 2.f)
    };
    Vector2 outOfViewPos = {0 - Settings::BIG_PANEL_SIZE.x - 10.f, inViewPos.y};
    Vector2 viewButtonSize = {50, 50};
    Vector2 viewButtonPos = {20.f, Settings::HEIGHT / 2.f};
    m_viewGroups.add(new ViewGroup(
        new AddRecipeView (outOfViewPos, inViewPos),
        new ExpandingButton(viewButtonSize, "Add recipe", viewButtonPos),
        ADD_VIEW
    ));

    inViewPos = {
        Settings::VIEW_X_ALIGNMENT, 
        (Settings::HEIGHT / 2.f) - (Settings::BIG_PANEL_SIZE.y / 2.f)
    };
    outOfViewPos = {Settings::WIDTH + Settings::BIG_PANEL_SIZE.x, inViewPos.y};

    m_viewGroups.add(new ViewGroup(
        new ModifyRecipeView(outOfViewPos, inViewPos),
        new ExpandingButton(viewButtonSize,"Modify Recipe", Vector2{viewButtonPos.x, viewButtonPos.y + (viewButtonSize.y * 1.5f)}),
        MODIFY_VIEW
    ));
}

Program::~Program(){
    m_viewGroups.clear();
}

void Program::run(){
    while (!WindowShouldClose())
    {
        float dt = m_frameTimer.getElapsed() / 1000;
        m_frameTimer.reset();
        handleInput();
        update(dt);    
        render();
    }
    CloseWindow();
}

void Program::handleInput(){
    for(ViewGroup* group : m_viewGroups){
        if(group->view->isVisible() || group->view->isInTransition()){
            group->view->handleInput();
        }
        if(!group->view->isInTransition()){
            group->button->handleInput();
        }
    }      
}

void Program::update(float dt){
    for(ViewGroup* group : m_viewGroups){
        if(group->view->isVisible() || group->view->isInTransition()){
            group->view->update(dt);
        }
    }   
}

void Program::render() const{
    BeginDrawing();
    ClearBackground(Settings::BACKGROUND_COLOR);
        for(ViewGroup* group : m_viewGroups){
            if(group->view->isVisible() || group->view->isInTransition()){
                group->view->render();
            }
            
            group->button->render();
        }     
    EndDrawing();
}


Program::ViewGroup* Program::getViewGroup(ViewType type)const{
    for(ViewGroup* group : m_viewGroups){
        if(group->type == type){
            return group;
        }
    }
    return nullptr;
}