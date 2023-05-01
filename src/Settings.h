#ifndef _Settings
#define _Settings

namespace Settings{
    inline constexpr const int WIDTH = (1920/2);
    inline constexpr const int HEIGHT = 1080 - 80;

    static Font font;
    static void loadFont(){
        font = LoadFontEx("assets/font.ttf", 32, NULL, 0);
    }
}

#endif