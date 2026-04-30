#pragma once
#include <cstddef>

template <typename T>
class Vector {
public:
    Vector();

    void push_back(const T& value);

    size_t size() const;

    const T& operator[](size_t index) const;

    T& operator[](size_t index);

private:
    T* _data         = nullptr;
    size_t _size     = 0;
    size_t _capacity = 2;

    void re_alloc(size_t new_capacity);
};

template <typename T>
inline Vector<T>::Vector() {
    re_alloc(2);
}

template <typename T>
inline void Vector<T>::re_alloc(size_t new_capacity) {
    T* new_block = new T[new_capacity];

    if (_size > new_capacity) {
        _size = new_capacity;
    }
    for (int i = 0; i < _size; i++) {
        new_block[i] = _data[i];
    }

    delete[] _data;
    _data     = new_block;
    _capacity = new_capacity;
}

template <typename T>
inline void Vector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        re_alloc(_capacity + _capacity / 2);
    }
    _data[_size] = value;
    _size++;
}

template <typename T>
inline size_t Vector<T>::size() const {
    return _size;
}

template <typename T>
inline const T& Vector<T>::operator[](size_t index) const {
    return _data[index];
}

template <typename T>
inline T& Vector<T>::operator[](size_t index) {
    return _data[index];
}
