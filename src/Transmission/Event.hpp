#ifndef _Event
#define _Event

#include "Recipe.hpp"

class Event
{
};

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

#endif