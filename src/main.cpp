#include "DataBase.h"
#include "Program.h"

int main(){
    EventBus* eventBus = new EventBus();
    DataBase db(eventBus);    
    Program prog(eventBus);
    prog.run();

    delete eventBus;
    return 0;
}