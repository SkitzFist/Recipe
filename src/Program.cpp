#include "Program.h"

#include "Settings.h"
#include "raylib.h"

#include "Ui/ExpandingButton.hpp"

#include "AddRecipeViewFactory.hpp"
#include "ModifyRecipeViewFactory.hpp"

Program::Program(EventBus* eventBus) :
    m_messageController(eventBus),
    m_modifyRecipeController(eventBus, ModifyRecipeViewFactory::create(eventBus)),
    m_addRecipeController(eventBus, AddRecipeViewFactory::create(eventBus)){
    
    m_addRecipeController.show();
}

Program::~Program(){
    
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
    m_messageController.handleInput();
    m_modifyRecipeController.handleInput();
    m_addRecipeController.handleUpdate();
}

void Program::update(float dt){
    m_messageController.update(dt);
    m_modifyRecipeController.update(dt);
    m_addRecipeController.update(dt);
}

void Program::render() const{
    BeginDrawing();
    ClearBackground(Settings::BACKGROUND_COLOR);
        m_modifyRecipeController.render();
        m_messageController.render();
        m_addRecipeController.render();
    EndDrawing();
}