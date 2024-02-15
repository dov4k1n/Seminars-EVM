//#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <class T> 
class Vector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    Vector();
    ~Vector();

    size_t getSize() const;
    T& operator[](size_t index);
    T& operator[](size_t index) const;

    void push_back(const T& element);
    void pop_back();
    void sort();

    class iterator {
    private:
        T* ptr;

    public:
        iterator(T* p) : ptr(p) {}

        T& operator*() const {
            return *ptr;
        }

        iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
    };

    iterator begin();
    iterator end();
    iterator begin() const;
    iterator end() const;
};

#include "vector.cpp"
#endif // VECTOR_H