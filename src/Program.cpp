#include "Program.h"

#include "Settings.h"
#include "StateStart.hpp"

#include "raylib.h"

Program::Program(){
    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    m_eventBus = new EventBus();
    m_stateSwitcher = new StateSwitcher(m_eventBus);
}

Program::~Program(){
    delete m_stateSwitcher;
    delete m_eventBus;
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

