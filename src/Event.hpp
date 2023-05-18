#ifndef _Event
#define _Event

#include <string>

struct Recipe
{
    int id;
    std::string name;
    std::string reference;
    std::string tags;
};

class Event{};

class SwitchStateToAddRecipe : public Event{};
class SwitchStateToGenerateRecipe : public Event{};
class SwitchStateToMainMenu : public Event{};

class PrepareAddRecipeEvent : public Event{};
class AddRecipeEvent : public Event{
public:
    Recipe recipe;
    AddRecipeEvent(const Recipe& _recipe):recipe(_recipe){}
};


class PrepareModifyRecipeEvent : Event{};
class ModifyRecipeEvent : Event{
    public:
    Recipe recipe;
    ModifyRecipeEvent(const Recipe& _recipe):recipe(_recipe){}
};

class ClearInputEvent : public Event{};

/////////////
///Search///
///////////
class SearchRecipeEvent : Event{
    public:
    std::string recipeName;
    SearchRecipeEvent(const std::string& name) : recipeName(name){}
};

class SearchFoundEvent : Event{
    public:
    Recipe recipe;
    SearchFoundEvent(Recipe _recipe) : recipe(_recipe){}
};

#endif