#ifndef _Settings
#define _Settings

namespace Settings{
    inline constexpr const int WIDTH = (1920/2);
    inline constexpr const int HEIGHT = 1080 - 80;

    //----------------------------------------------------------------------------------
    // Colors
    //----------------------------------------------------------------------------------   

    //green hell
    #define BACKGROUND_COLOR CLITERAL(Color){0, 0, 0, 255}
    #define TITLE_COLOR CLITERAL(Color){102, 204, 102, 255}

    #define BUTTON_COLOR CLITERAL(Color){102, 204, 102, 255}
    #define BUTTON_HOVERING_COLOR CLITERAL(Color){132, 224, 132, 255}
    #define BUTTON_SHADOW_COLOR CLITERAL(Color){51, 102, 51, 255}
    #define BUTTON_TEXT_COLOR CLITERAL(Color){0, 0, 0, 255}
    #define BUTTON_SWITCH_COLOR CLITERAL(Color){255, 102, 102, 255}
    #define BUTTON_SWITCH_SHADOW_COLOR CLITERAL(Color){128, 51, 51, 255}

    #define INPUT_BACKGROUND_COLOR CLITERAL(Color){230, 230, 230, 255}
    #define INPUT_BACKGROUND_FOCUSED_COLOR CLITERAL(Color){255, 255, 255, 255}
    #define INPUT_TITLE_COLOR CLITERAL(Color){100, 100, 100, 255}
    #define INPUT_TEXT_COLOR CLITERAL(Color){50, 50, 50, 255}

    //Grey
    #define BUTTON_COLOR_GRAY CLITERAL(Color){102, 204, 102, 255}
    #define BUTTON_HOVERING_COLOR_GRAY CLITERAL(Color){132, 224, 132, 255}
    #define BUTTON_SHADOW_COLOR_GRAY CLITERAL(Color){51, 102, 51, 255}
    #define BUTTON_TEXT_COLOR_GRAY CLITERAL(Color){0, 0, 0, 255}
    #define BUTTON_SWITCH_COLOR_GRAY CLITERAL(Color){255, 102, 102, 255}
    #define BUTTON_SWITCH_SHADOW_COLOR_GRAY CLITERAL(Color){128, 51, 51, 255}
    #define INPUT_BACKGROUND_COLOR_GRAY CLITERAL(Color){230, 230, 230}
}

#endif