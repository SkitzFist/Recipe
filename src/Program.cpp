#include "Program.h"

#include "Settings.h"
#include "StateStart.hpp"

#include "raylib.h"

Program::Program(EventBus* eventBus){
    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetWindowPosition(GetScreenWidth(), 25.f);
    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    m_stateSwitcher = new StateSwitcher(eventBus);
    Settings::loadFont();
}

Program::~Program(){
    delete m_stateSwitcher;
}

void Program::run(){
    while (!WindowShouldClose())
    {
        State* state = m_stateSwitcher->getCurrentState();
        handleInput(state);
        update(state);    
        render(state);
    }
    CloseWindow();
}

void Program::handleInput(State* state){
    if(state){
        state->handleInput();
    }
}

void Program::update(State* state){
    float dt = GetFrameTime();
    if(state){
        state->update(dt);
    }
}

void Program::render(State* state) const{
    BeginDrawing();
    ClearBackground(BLACK);
    if(state){
        state->render();
    }
    EndDrawing();
}

