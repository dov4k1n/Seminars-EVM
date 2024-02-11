#include "vector.h"

template <class T>
Vector<T>::Vector() : data(nullptr), size(0), capacity(0) {}

template <class T>
Vector<T>::~Vector() {
    if (data) {
        delete[] data;
    }
}

template <class T>
size_t Vector<T>::getSize() const {
    return size;
}

template <class T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index]; 
}

template <class T>
T& Vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index]; 
}

template <class T>
void Vector<T>::push_back(const T& newElement) {
    if (size == capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;

        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        if (data) delete[] data;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = newData[i];
        }
        delete[] newData;
    }

    data[size++] = newElement;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vector) {
    for (int i = 0; i < vector.getSize() - 1; i++) {
        out << vector[i] << " ";
    }
    out << vector[vector.getSize() - 1];
    return out;
}

template <class T>
std::istream& operator>>(std::istream& in, Vector<T>& vector) {
    T newElement;
    in >> newElement;
    vector.push_back(newElement);
    return in;
}