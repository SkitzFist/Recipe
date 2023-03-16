#ifndef _Random
#define _Random

#include <random>

namespace Random{
    static std::random_device rd;
    static std::mt19937_64 mt(rd());

    static int INTEGER(int min, int max){
        std::uniform_int_distribution<int> dst(min,max);
        return dst(rd);
    }
}

#endif