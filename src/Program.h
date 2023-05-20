#ifndef _Program
#define _Program

#include "EventBus.hpp"

#include "Timer.hpp"
#include "views/view.h"
#include "UiButton.hpp"

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
    
    View* m_addRecipeView;
    std::vector<UiButton*> m_buttons;
};

#endif