#ifndef _Program
#define _Program

#include <memory>

#include "EventHandler.hpp"
#include "Array.hpp"
#include "Timer.hpp"
#include "Views/view.h"
#include "Ui/UiButton.hpp"


class Program : public EventHandler<ToggelAddRecipeViewEvent>, public EventHandler<ToggelModifyRecipeViewEvent>{
public:
    enum ViewType{
        ADD_VIEW,
        MODIFY_VIEW   
    };

    class ViewGroup{
    public:
        View* view;
        UiButton* button;
        ViewType type;
        ViewGroup(View* _view, UiButton* _button, ViewType _type)
            :view(_view), button(_button), type(_type)
        {}

        ~ViewGroup(){
            delete view;
            delete button;
        }        
    };

public:
    Program(EventBus* eventBus);
    ~Program();
    void run();

    //////////////////////////////////////////////////////
    ///Event Handlers/////////////////////////////////////                                  
    void onEvent(const ToggelAddRecipeViewEvent& event);
    void onEvent(const ToggelModifyRecipeViewEvent& event);
    /////////////////////////////////////////////////////

private:
    Timer m_frameTimer;

    void handleInput();
    void update(float dt);
    void render() const;

    Array<ViewGroup*> m_viewGroups;
    ViewGroup* getViewGroup(ViewType type) const; 

    ///Event
    void toggleView(ViewType type);
};

#endif