#include "DataBase.h"
#include "Program.h"

int main(){
    EventBus* eventBus = new EventBus();
    DataBase db(eventBus);

    InitWindow(Settings::WIDTH, Settings::HEIGHT, "Recipe");
    SetWindowPosition(GetScreenWidth(), 25.f);
    SetTargetFPS(144);
    SetExitKey(KEY_ESCAPE);
    Settings::FONT_SIZE = GetFontDefault().baseSize * 4;

    Program prog(eventBus);
    prog.run();


    delete eventBus;
    return 0;
}