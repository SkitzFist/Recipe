#ifndef _Settings
#define _Settings

#include "raylib.h"

namespace Settings{
    inline constexpr const int WIDTH = (1920/2);
    inline constexpr const int HEIGHT = 1080 - 80;

    //Text
    inline int FONT_SIZE;


    // View
        //General
        inline constexpr const float VIEW_TRANSITION_DURATION_MS = 800.f;
        //Big view
        inline constexpr const Vector2 BIG_VIEW_SIZE = {WIDTH * 0.8f, HEIGHT * 0.8f};
        inline constexpr const int VIEW_X_ALIGNMENT = WIDTH * 0.1f;

        //Message view
        inline constexpr const Vector2 MESSAGE_VIEW_MAX_SIZE = {WIDTH * 0.4f, HEIGHT * 0.2f};
        inline constexpr const float MESSAGE_VIEW_MAX_WIDTH = WIDTH * 0.4f;

    //todo enscapsulate in namespace
    ////////////////////////////////////////////////////////////////////////////////////
    //                        COLORS  
        //General
        inline constexpr const Color BACKGROUND_COLOR = {40, 40, 40, 255};
        inline constexpr const Color Title = {144, 238, 144, 255};

        //view
        inline constexpr const Color VIEW_BACKGROUND_COLOR = {200, 200, 200, 185};
        
        //Button
        inline constexpr const Color BUTTON_COLOR = {30, 144, 255, 255};
        inline constexpr const Color BUTTON_HOVER_COLOR = {0, 191, 255, 255};
        inline constexpr const Color BUTTON_TEXT_COLOR = {255, 255, 255, 255};
    //////////////////////////////////////////////////////////////////////////////////////

    
    //todo make inline
    #define INPUT_BACKGROUND_COLOR CLITERAL(Color){230, 230, 230, 255}
    #define INPUT_BACKGROUND_FOCUSED_COLOR CLITERAL(Color){255, 255, 255, 255}
    #define INPUT_TITLE_COLOR CLITERAL(Color){100, 100, 100, 255}
    #define INPUT_TEXT_COLOR CLITERAL(Color){50, 50, 50, 255}
    
}

#endif