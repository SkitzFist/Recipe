#ifndef _Log
#define _Log

#include <string>

#include "raylib.h"

namespace Log
{
    //info
    static inline void info(const char* log){
        TraceLog(LOG_INFO, log);
    }

    static inline void info(const std::string& str){
        TraceLog(LOG_INFO,str.c_str());
    }

    static inline void info(const std::string& _str , Vector2 vec){
        std::string str = _str + ": " + std::to_string(vec.x) + " , " + std::to_string(vec.y);
        TraceLog(LOG_INFO, str.c_str());
    }

    //Error
    static inline void error(const char* log){
        TraceLog(LOG_ERROR, log);
    }

    static inline void error(const std::string& str){
        TraceLog(LOG_ERROR,str.c_str());
    }

    static inline void error(const std::string& _str , Vector2 vec){
        std::string str = _str + ": " + std::to_string(vec.x) + " , " + std::to_string(vec.y);
        TraceLog(LOG_ERROR, str.c_str());
    }    
}

#endif