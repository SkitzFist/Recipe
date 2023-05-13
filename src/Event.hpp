#ifndef _Event
#define _Event

#include <string>

struct Recipe
{
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
    Recipe recipe;
    ModifyRecipeEvent(const Recipe& _recipe):recipe(_recipe){}
};

class ClearInputEvent : public Event{};

class SearchRecipeEvent : public Event{
    std::string recipeName;
    SearchRecipeEvent(const std::string& name) : recipeName(name){}
};

#endif