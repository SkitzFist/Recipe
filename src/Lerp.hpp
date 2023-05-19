#ifndef _Lerp
#define _Lerp

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
}

#endif