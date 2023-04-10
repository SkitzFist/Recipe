#ifndef _Log
#define _Log

#include "raylib.h"

static void log(const char* log){
    TraceLog(LOG_INFO, log);
}


#endif