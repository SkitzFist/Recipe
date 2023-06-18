#include "TabCycling.h"

TabCycling::TabCycling():
    m_inputFields(4){
}

TabCycling::TabCycling(TabCycling&& src) noexcept:
    m_inputFields(std::move(src.m_inputFields)){
}

void TabCycling::handleInput(){
    if(IsKeyPressed(KEY_TAB)){
        if(IsKeyDown(KEY_LEFT_SHIFT)){
            backWardCycle();
        }else{
            forwardCycle(); 
        }
    }
}

void TabCycling::addInputField(InputField *InputField){
    m_inputFields.add(InputField);
}

void TabCycling::forwardCycle(){
    int lastIndex = m_inputFields.size() - 1;
    bool tabSuccessful = false;
    for(int i = 0; i < m_inputFields.size(); ++i){
        if(m_inputFields[i]->isFocused()){
            int nextIndex = i + 1;
            
            if(nextIndex > lastIndex){
                nextIndex = 0;
            }
            m_inputFields[i]->onBlur();
            m_inputFields[nextIndex]->onFocus();
            tabSuccessful = true;
            break;
        }
    }

    if(!tabSuccessful){
        m_inputFields[0]->onFocus();
    }
}

void TabCycling::backWardCycle(){
    int lastIndex = m_inputFields.size() - 1;
    bool tabSuccessful = false;
    for (int i = 0; i < m_inputFields.size(); ++i)
    {
        if (m_inputFields[i]->isFocused())
        {
            int nextIndex = i - 1;

            if (nextIndex < 0)
            {
                nextIndex = lastIndex;
            }

            m_inputFields[i]->onBlur();
            m_inputFields[nextIndex]->onFocus();
            tabSuccessful = true;
            break;
        }
    }

    if (!tabSuccessful)
    {
        m_inputFields[lastIndex]->onFocus();
    }
}

