#ifndef _Signal
#define _Signal

#include <functional>
#include <map>

template <typename... Args>
class Signal
{
public:
    Signal() : m_currentID(0) {}

    Signal(Signal const &) = delete;
    Signal &operator=(Signal const &) = delete;
    
    Signal(Signal&& other) noexcept 
        : m_currentID(other.m_currentID), m_slots(std::move(other.m_slots)) {
        other.reset();
    }

    Signal& operator=(Signal&& other) noexcept {
        if (this != &other) {
            m_currentID = other.m_currentID;
            m_slots = std::move(other.m_slots);
            other.reset();
        }
        return *this;
    }

    int connect(std::function<void(Args...)> const &slot) const
    {
        m_slots.insert(std::make_pair(++m_currentID, slot));
        return m_currentID;
    }

    void disconnect(int id) const
    {
        m_slots.erase(id);
    }

    void disconnectAll() const
    {
        m_slots.clear();
    }

    void emit(Args... p)
    {
        for (auto it : m_slots)
        {
            it.second(p...);
        }
    }

private:
    mutable int m_currentID;
    mutable std::map<int, std::function<void(Args...)>> m_slots;

    void reset() const {
        m_currentID = 0;
        m_slots.clear();
    }
};

#endif