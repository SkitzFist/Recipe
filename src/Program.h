#ifndef _Program
#define _Program

#include <memory>
#include "Array.hpp"
#include "Timer.hpp"
#include "View.h"
#include "Ui/UiButton.hpp"
#include "Transmission/EventBus.hpp"

#include "MessageController.hpp"
#include "ModifyRecipeController.hpp"
#include "AddRecipeController.hpp"

class Program{
public:
    Program(EventBus* eventBus);
    ~Program();
    void run();

private:
    Timer m_frameTimer;

    void handleInput();
    void update(float dt);
    void render() const;

    MessageController m_messageController;
    ModifyRecipeController m_modifyRecipeController;
    //AddRecipeController m_addRecipeController;
};

#endif