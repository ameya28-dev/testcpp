#pragma once
#include <cstddef>
#include <cstdlib>
#include <iostream>

#ifndef ARRAY_H
#define ARRAY_H

template <typename T, size_t S>
class Array {
   private:
    T arr[S]{};

   public:
    T& operator[](size_t);
    const T& operator[](size_t) const;
    constexpr size_t getSize();
    void display();
};

#endif

template <typename T, size_t S>
T& Array<T, S>::operator[](size_t index) {
    if (index >= S) {
        static_assert("Range out of bounds");
    }
    return arr[index];
}

template <typename T, size_t S>
inline const T& Array<T, S>::operator[](size_t index) const {
    if (index >= S) {
        static_assert("Range out of bounds");
    }
    return arr[index];
}

template <typename T, size_t S>
constexpr size_t Array<T, S>::getSize() {
    return S;
}

template <typename T, size_t S>
inline void Array<T, S>::display() {
    for (size_t i = 0; i < S; i++) {
        std::cout << arr[i] << '\t';
    }
    std::cout << std::endl;
}
