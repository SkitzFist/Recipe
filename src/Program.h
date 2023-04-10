#ifndef _Program
#define _Program

#include "State.hpp"

class Program{
public:
    Program();
    ~Program();
    void run();

private:
    State* m_state;
    
    void handleInput();
    void update();
    void render() const;
};

#endif