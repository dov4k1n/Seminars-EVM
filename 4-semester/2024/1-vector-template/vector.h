//#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
// #include <algorithm>
#include <stdexcept>
// #include <vector>

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
};

#include "vector.cpp"
#endif // VECTOR_H