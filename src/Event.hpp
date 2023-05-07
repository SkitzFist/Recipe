#ifndef _Event
#define _Event

#include <string>

class Event{};

class SwitchStateToAddRecipe : public Event{};
class SwitchStateToGenerateRecipe : public Event{};
class SwitchStateToMainMenu : public Event{};

class PrepareAddRecipe : public Event{};

struct Recipe
{
    std::string name;
    std::string reference;
    std::string tags;
};

class AddRecipe : public Event{
public:
    Recipe recipe;
    AddRecipe(const Recipe& _recipe):recipe(_recipe){}
};

class SwitchModeEvent : Event {};

#endif