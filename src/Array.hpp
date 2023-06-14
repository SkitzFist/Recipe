#ifndef _Array
#define _Array

#include <utility>
#include <type_traits>
#include "Log.hpp"

template <class T>
class Array{
private:
    class Iterator {
    public:
        Iterator(T* ptr) : ptr(ptr) {}

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        const T& operator*() const {
            return *ptr;
        }

        T& operator*() {
            return *ptr;
        }

    private:
        T* ptr;
    };

public:
    Array(unsigned int _capacity = 10);
    ~Array();
    const int size() const;
    const int capacity() const{
        return m_capacity;
    }

    void add(const T& item);
    void add(T&& item);

    void remove(unsigned int _index);

    const T& operator[](unsigned int _index) const;
    T& operator[](unsigned int _index);
    void clear();
    void reallocate(unsigned int _newCapacity);
    Iterator begin()const{return m_data;}
    Iterator end()const{return m_data+m_size;}
    Iterator begin(){return m_data;}
    Iterator end(){return m_data+m_size;}
    const bool isEmpty() const;
private:
    unsigned int m_size;
    unsigned int m_capacity;
    T* m_data;
};

template <class T>
Array<T>::Array(unsigned int _capacity)
    :m_size(0), m_capacity(_capacity){
    if(m_capacity > 0){
        m_data = (T*)::operator new(m_capacity * sizeof(T));
    }
}

template <class T>
Array<T>::~Array(){
    if(m_capacity > 0){
        clear();
        ::operator delete(m_data);
    }
}

template <class T>
const int Array<T>::size() const{
    return m_size;
}

template <class T>
void Array<T>::add(const T& item){
    if(m_size >= m_capacity){
        int newCapacity = m_capacity * 2;
        if(newCapacity == 0){
            newCapacity += 1;
        }
        reallocate(newCapacity);
    }
    m_data[m_size++] = item;
}

template <class T>
void Array<T>::add(T&& item){
    if(m_size >= m_capacity){
        int newCapacity = m_capacity * 2;
        if(newCapacity == 0){
            newCapacity += 1;
        }
        reallocate(newCapacity);
    }
    m_data[m_size++] = std::move(item);
    }

template <class T>
void Array<T>::remove(unsigned int _index){
    if(!(_index >= 0 && _index < m_size)){
        return;
    }
    m_data[_index].~T();
    m_data[_index] = m_data[--m_size];
}

template <class T>
const T& Array<T>::operator[](unsigned int _index) const{
    return m_data[_index];
}

template <class T>
T& Array<T>::operator[](unsigned int _index){
    return m_data[_index];
}

template <class T>
void Array<T>::clear(){
    if constexpr (std::is_pointer_v<T>) {
        for (unsigned int i = 0; i < m_size; ++i) {
            delete m_data[i];
        }
    } else {
        for (unsigned int i = 0; i < m_size; ++i) {
            m_data[i].~T();
        }
    }
    m_size = 0;
}

//Todo::Check if T is pointer, in that case, delete memory or make another method for it. update: array should not delete memory, it's not responsible for memory deletion.

template <class T>
void Array<T>::reallocate(unsigned int _newCapacity){
    T* tmp = (T*)::operator new(_newCapacity * sizeof(T));

    for(unsigned int i = 0; i < m_size; ++i){
        tmp[i] = std::move(m_data[i]);
    }

    for(unsigned int i = 0; i < m_size; ++i){
        m_data[i].~T();
    }

    if(m_capacity > 0){
        ::operator delete(m_data);    
    }

    m_data = tmp;
    m_capacity  = _newCapacity;
}

template <class T>
const bool Array<T>::isEmpty() const{
    return m_size == 0;
}

#endif