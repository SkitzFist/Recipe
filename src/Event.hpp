#ifndef _Event
#define _Event

class Event{};

class SwitchStateToAddRecipe : public Event{};
class SwitchStateToGenerateRecipe : public Event{};
class SwitchStateToMainMenu : public Event{};

class AddRecipe : public Event{};

#endif