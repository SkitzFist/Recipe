#include "Program.h"

#include "Settings.h"
#include "raylib.h"

Program::Program(EventBus* eventBus){
    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetWindowPosition(GetScreenWidth(), 25.f);
    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    
    Vector2 viewSize = {Settings::WIDTH / 4.f, Settings::HEIGHT * 0.1f};
    Vector2 inViewPos = {
        (Settings::WIDTH / 2.f) - (viewSize.x / 2.f),
        Settings::HEIGHT - (viewSize.y * 2.f)
    };
    Vector2 outOfViewPos  = {
        inViewPos.x,
        Settings::HEIGHT + viewSize.y
    };
    m_view = new View(outOfViewPos, inViewPos, viewSize);
}

Program::~Program(){
    delete m_view;
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
    
}

void Program::update(float dt){
    m_view->update(dt);
}

void Program::render() const{
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
        m_view->render();
    EndDrawing();
}

