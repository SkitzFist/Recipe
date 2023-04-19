#ifndef _Log
#define _Log

#include <string>

#include "raylib.h"

static inline void log(const char* log){
    TraceLog(LOG_INFO, log);
}

static inline void log(const std::string& str){
    TraceLog(LOG_INFO,str.c_str());
}

static inline void log(const std::string& _str , Vector2 vec){
    std::string str = _str + ": " + std::to_string(vec.x) + " , " + std::to_string(vec.y);
    TraceLog(LOG_INFO, str.c_str());
}


#endif