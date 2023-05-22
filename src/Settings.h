#ifndef _Settings
#define _Settings

#include "raylib.h"

namespace Settings{
    inline constexpr const int WIDTH = (1920/2);
    inline constexpr const int HEIGHT = 1080 - 80;
    inline constexpr const int X_ALIGNMENT = HEIGHT * 0.1f;

    //----------------------------------------------------------------------------------
    // Colors
    //----------------------------------------------------------------------------------   
        //General
        inline constexpr const Color BACKGROUND_COLOR = {40, 40, 40, 255};
        inline constexpr const Color Title = {144, 238, 144, 255};

        //view
        inline constexpr const Color VIEW_BACKGROUND_COLOR = {200, 200, 200, 185};
        
        //Button
        inline constexpr const Color BUTTON_COLOR = {30, 144, 255, 255};
        inline constexpr const Color BUTTON_HOVER_COLOR = {0, 191, 255, 255};
        inline constexpr const Color BUTTON_TEXT_COLOR = {255, 255, 255, 255};

    
    //todo make inline
    #define INPUT_BACKGROUND_COLOR CLITERAL(Color){230, 230, 230, 255}
    #define INPUT_BACKGROUND_FOCUSED_COLOR CLITERAL(Color){255, 255, 255, 255}
    #define INPUT_TITLE_COLOR CLITERAL(Color){100, 100, 100, 255}
    #define INPUT_TEXT_COLOR CLITERAL(Color){50, 50, 50, 255}

    
}

#endif