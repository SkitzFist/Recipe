#ifndef _StateStart
#define _StateStart

#include "UiElement.hpp"
#include "State.hpp"


class StateStart : public State{
public:
StateStart(EventBus* _eventBus);
virtual ~StateStart();

virtual void handleInput() override;
virtual void update(float dt) override;
virtual void render() const override;

private:
   std::vector<UiElement*> m_uiElements;
   UiElement* m_hoveredUiElement;
};

#endif