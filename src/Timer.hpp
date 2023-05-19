#ifndef _Timer
#define _Timer

#include <chrono>

class Timer {
public:
    Timer(float duration = 0.f) : m_duration(duration) {
        m_startTime = std::chrono::high_resolution_clock::now();
    }

    inline float getElapsed() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> elapsed = end_time - m_startTime;
        return elapsed.count();
    }

    inline float getTime() const {
        return getElapsed() / m_duration;
    }

    inline bool hasElapsed() const{
        return getElapsed() >= m_duration;
    }

    inline void reset(){
        m_startTime = std::chrono::high_resolution_clock::now();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    float m_duration;
};

#endif