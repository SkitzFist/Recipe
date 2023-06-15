#ifndef _Event
#define _Event

#include "Recipe.hpp"

class Event
{
};



//////////////Recipe events/////////////////////////////////////
//Add
class AddRecipeEvent : Event{
public:
    Recipe recipe;
    AddRecipeEvent(const Recipe &_recipe) : recipe(_recipe) {}
};

//Modify
class ModifyRecipeEvent : Event{
public:
    Recipe recipe;
    ModifyRecipeEvent(const Recipe &_recipe) : recipe(_recipe) {}
};


//Search
class SearchRecipeEvent : Event
{
public:
    std::string recipeName;
    SearchRecipeEvent(const std::string &name) : recipeName(name) {}
};

class SearchFoundEvent : Event
{
public:
    Recipe recipe;
    SearchFoundEvent(Recipe _recipe) : recipe(_recipe) {}
};


///////////Other events/////////////////////////////////////
class AddMessageEvent : public Event{
public:
    std::string title;
    std::string text;
    std::string buttonText;

    AddMessageEvent(const std::string& _title, const std::string& _text, const std::string& _buttonText = "Close"):
        title(_title), text(_text), buttonText(_buttonText){}
};

#endif