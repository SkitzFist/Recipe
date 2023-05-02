#ifndef _Event
#define _Event

class Event{};

class SwitchStateToAddRecipe : public Event{};
class SwitchStateToGenerateRecipe : public Event{};
class SwitchStateToMainMenu : public Event{};

class PrepareAddRecipe : public Event{};
class AddRecipe : public Event{
public:
    std::vector<std::string> entry;
    AddRecipe(const std::vector<std::string> _entry):entry(_entry){}
};

#endif