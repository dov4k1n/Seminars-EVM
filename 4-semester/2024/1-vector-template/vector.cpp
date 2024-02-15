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
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;

        if (size < capacity / 2 && capacity > 1) {
            capacity /= 2;

            T* newData = new T[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
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
void Vector<T>::sort() {
    std::sort(data, data + size);
}

// template <class T>
// std::ostream& operator<<(std::ostream& out, const Vector<T>& vector) {
//     out << "[";
//     for (const auto& element : vector) {
//         out << element << ", ";
//     }
//     out << "]";
//     return out;
// }

// template <class T>
// std::istream& operator>>(std::istream& in, Vector<T>& vector) {
//     // Assuming elements are separated by spaces
//     T newElement;
//     while (in >> newElement) {
//         vector.push_back(newElement);
//     }
//     return in;
// }