#ifndef _TabCycling
#define _TabCycling

#include "Array.hpp"
#include "Ui/InputField.hpp"

class TabCycling{
public:
    TabCycling();
    TabCycling(TabCycling&& src) noexcept;
    void handleInput();
    void addInputField(InputField* InputField);


private:
    Array<InputField*> m_inputFields;

    void forwardCycle();
    void backWardCycle();
};

#endif