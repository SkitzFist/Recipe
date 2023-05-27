#ifndef _Signal
#define _Signal

#include <functional>
#include <map>

class ID
{
public:
    virtual ~ID() = default;
    virtual int getID() const = 0;
};

template <typename... Args>
class Signal
{
public:
    Signal() : m_currentID(0) {}

    Signal(Signal const &) = delete;
    Signal(Signal &&) = delete;
    Signal &operator=(Signal const &) = delete;
    Signal &operator=(Signal &&) = delete;

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
};

#endif