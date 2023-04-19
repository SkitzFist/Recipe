#ifndef _StateStart
#define _StateStart

#include "UiElement.hpp"
#include "State.hpp"


class StateStart : public State, public EventHandler<AddRecipeButtonPressed>{
public:
StateStart(EventBus* _eventBus);
virtual ~StateStart();

virtual State* handleInput() override;
virtual State* update(float dt) override;
virtual void render() const override;

virtual void onEvent(const AddRecipeButtonPressed& _event) override;

private:
   State* m_state;
   std::vector<UiElement*> m_uiElements;
   UiElement* m_hoveredUiElement;
};

#endif