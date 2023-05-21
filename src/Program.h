#ifndef _Program
#define _Program

#include <memory>

#include "EventBus.hpp"
#include "Timer.hpp"
#include "Views/view.h"
#include "Ui/UiButton.hpp"
#include "EventHandler.hpp"

class Program : public EventHandler<ToggelAddRecipeViewEvent>{
public:
    enum ViewType{
        ADD_STATE   
    };

    class ViewGroup{
    public:
        std::unique_ptr<View> view;
        std::unique_ptr<UiButton> button;
        ViewType type;
        ViewGroup(std::unique_ptr<View> _view, std::unique_ptr<UiButton> _button, ViewType _type)
            :view(std::move(_view)), button(std::move(_button)), type(_type){}
    };

public:
    Program(EventBus* eventBus);
    ~Program();
    void run();

    //////////////////////////////////////////////////////
    ///Event Handlers/////////////////////////////////////                                  
    void onEvent(const ToggelAddRecipeViewEvent& event);
    /////////////////////////////////////////////////////

private:
    Timer m_frameTimer;

    void handleInput();
    void update(float dt);
    void render() const;

    const int getViewGroupIndex(ViewType type) const;
    std::vector<ViewGroup> m_viewGroups;
};

#endif