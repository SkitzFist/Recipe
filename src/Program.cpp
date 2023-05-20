#include "Program.h"

#include "Settings.h"
#include "raylib.h"

#include "views/AddRecipeView.h"

Program::Program(EventBus* eventBus){
    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetWindowPosition(GetScreenWidth(), 25.f);
    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    
    m_addRecipeView = new AddRecipeView();
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
    if(IsKeyPressed(KEY_SPACE)){
        m_addRecipeView->toggleVisibility();
    }    
}

void Program::update(float dt){
    m_addRecipeView->update(dt);
}

void Program::render() const{
    BeginDrawing();
    ClearBackground(BLACK);
        m_addRecipeView->render();        
    EndDrawing();
}

