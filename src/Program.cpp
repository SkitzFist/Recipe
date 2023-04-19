#include "Program.h"

#include "Settings.h"
#include "StateStart.hpp"

#include "raylib.h"

Program::Program(){
    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    m_eventBus = new EventBus();
    m_state = new StateStart(m_eventBus);
}

Program::~Program(){
    delete m_eventBus;
    delete m_state;
}

void Program::run(){
    while (!WindowShouldClose())
    {
        handleInput();
        update();
        render();
    }
    CloseWindow();
}

void Program::handleInput(){
    if(m_state){
        m_state = m_state->handleInput();
    }
}

void Program::update(){
    float dt = GetFrameTime();
    if(m_state){
        m_state = m_state->update(dt);
    }
}

void Program::render() const{
    BeginDrawing();
    ClearBackground(BLACK);
    if(m_state){
        m_state->render();
    }
    EndDrawing();
}

