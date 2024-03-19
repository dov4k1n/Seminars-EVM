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
    void quicksort(T* start, T* end);
    void sort();
    void print();

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    bool operator<=(const Vector& other) const;
    bool operator<(const Vector& other) const;
    bool operator>=(const Vector& other) const;
    bool operator>(const Vector& other) const;

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
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        if (data) delete[] data;
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = newData[i];
        }
        delete[] newData;
    }

    data[size++] = newElement;
}

template <class T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;

        if (size < capacity / 2 && capacity > 1) {
            capacity /= 2;

            T* newData = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                data[i] = newData[i];
            }
            delete[] newData;
        }
    }
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
    return iterator(data);
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() {
    return iterator(data + size);
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin() const {
    return iterator(data);
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() const {
    return iterator(data + size);
}

template <class T>
void Vector<T>::quicksort(T* start, T* end) {
    if (start < end) {
        T* pivot = start;
        T* left = start + 1;
        T* right = end;

        while (left <= right) {
            while (left <= end && *left < *pivot) {
                ++left;
            }
            while (right > start && *right >= *pivot) {
                --right;
            }
            if (left < right) {
                std::swap(*left, *right);
            }
        }

        std::swap(*pivot, *right);

        quicksort(start, right - 1);
        quicksort(right + 1, end);
    }
}

template <class T>
void Vector<T>::sort() {
    quicksort(data, data + size - 1);
}

template <class T>
void Vector<T>::print() {
    std::cout << "[";
    auto it = begin();
    if (it != end()) {
        std::cout << *it;
        ++it;
    }
    while (it != end()) {
        std::cout << ", " << *it;
        ++it;
    }
    std::cout << "]" << std::endl;
}

template <class T>
bool Vector<T>::operator==(const Vector& other) const {
    if (size != other.getSize())
        return false;

    auto it = begin();
    auto it_other = other.begin();

    while (it != end() && it.other != other.end()) {
        if (*it != *it_other)
            return false;
    }

    return true;
}

template <class T>
bool Vector<T>::operator!=(const Vector& other) const {

}

template <class T>
bool Vector<T>::operator<=(const Vector& other) const {

}

template <class T>
bool Vector<T>::operator<(const Vector& other) const {

}

template <class T>
bool Vector<T>::operator>=(const Vector& other) const {

}

template <class T>
bool Vector<T>::operator>(const Vector& other) const {

}