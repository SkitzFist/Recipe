#ifndef _Lerp
#define _Lerp

#include <cmath>

namespace Lerp
{
    inline constexpr const float lerp(float time, float startValue, float endValue){
       return (endValue - startValue) * time + startValue;
    }

    inline constexpr const unsigned char lerp(float time, unsigned char startValue, unsigned char endValue){
        return (endValue - startValue) * time + startValue;
    }

    inline constexpr const float linear(float time){
        return time;
    }

    inline constexpr const float smoothStop(float time){
        float x = 1.f - time;
        return 1.f - (x * x);
    }

    inline constexpr const float smoothStop2(float time){
        float x = 1.f - time;
        return 1.f - (x * x * x);
    }

    inline constexpr const float smoothStop3(float time){
        float x = 1.f - time;
        return 1.f - (x * x * x * x);
    }

    inline constexpr const float smoothStart(float time){
        return time * time;
    }

    inline constexpr const float smoothStart2(float time){
        return time * time * time;
    }

    inline constexpr const float smoothStart3(float time){
        return time * time * time * time; 
    }

    inline constexpr const float smoothStep(float time){
        return Lerp::lerp(time, Lerp::smoothStart(time), Lerp::smoothStop(time));
    }

    inline constexpr const float smoothStep2(float time){
        return Lerp::lerp(time, Lerp::smoothStart2(time), Lerp::smoothStop2(time));
    }

    inline constexpr const float smoothStep3(float time){
        return Lerp::lerp(time, Lerp::smoothStart3(time), Lerp::smoothStop3(time));
    }

    inline constexpr const float overshoot(float time){
        const float s = 1.70158f;; 
        return time * time * ((s + 1) * time - s);
    }

    inline constexpr const float snapIn(float time){
        if (time < 0.9f)
            return Lerp::smoothStart3(time / 0.9f);
        else
            return 1 + (time - 0.9f) * 10;
    }

    inline constexpr const float easeOutBack(float time){
        const float c1 = 1.70158f;
        const float c3 = c1 + 1;

        float x = time - 1;
        float x2 = x * x; 
        float x3 = x2 * x;
        
        return 1 + c3 * x3 + c1 * x2;
    }

    inline constexpr const float easeOutElastic(float time){
        const float c4 = PI / 2.f;

        if(time == 0.f)
            return 0.f;
        if(time == 1.f)
            return 1.f;

    return powf(2.f, -10.f * time) * sinf((time * 10.f - 0.75f) * c4) + 1.f;
}
}

#endif