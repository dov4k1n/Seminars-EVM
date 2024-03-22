#include <iostream>
#include <algorithm>

template <class T>
class Vector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    Vector(): data(nullptr), size(0), capacity(0) {}

    Vector(const Vector& other): 
        size(other.size), 
        capacity(other.capacity) 
    {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            size = other.size;
            capacity = other.capacity;
            delete[] data;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Vector() { delete[] data; }

    void push_back(const T& newElement) {
        if (size == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;

            T* newData = new T[capacity];

            for (size_t i = 0; i < size; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;

            // for (size_t i = 0; i < size; i++) {
            //     data[i] = newData[i];
            // }

            //delete[] newData;
        }

        data[size++] = newElement;
    }
};

int main() {
    Vector<int> a;
    a.push_back(1);

    Vector<Vector<int>> c;
    c.push_back(a);
    
    return 0;
}