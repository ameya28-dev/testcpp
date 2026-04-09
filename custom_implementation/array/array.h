#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <cstdlib>
#include <iterator>

template <typename T>
class ArrayIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

public:
    ArrayIterator(pointer ptr) : _ptr(ptr) {}

    ArrayIterator& operator++() {
        _ptr++;
        return *this;
    }

    ArrayIterator operator++(int) {
        ArrayIterator<T> iterator = *this;
        ++(*this);
        return iterator;
    }

    ArrayIterator& operator--() {
        _ptr--;
        return *this;
    }

    ArrayIterator operator--(int) {
        ArrayIterator<T> iterator = *this;
        --(*this);
        return iterator;
    }

    reference operator[](size_t index) {
        return *(_ptr + index);
    }

    pointer operator->() {
        return _ptr;
    }

    reference operator*() {
        return *_ptr;
    }

    reference operator*() const {
        return *_ptr;
    }

    bool operator==(const ArrayIterator& other) const {
        return _ptr == other._ptr;
    }

    bool operator!=(const ArrayIterator& other) const {
        return !(*this == other);
    }

    ArrayIterator operator+(difference_type n) const {
        return ArrayIterator(_ptr + n);
    }

private:
    pointer _ptr;
};

template <typename T, size_t S>
class Array {
public:
    using ValueType     = T;
    using Iterator      = ArrayIterator<T>;
    using ConstIterator = ArrayIterator<const T>;

public:
    T& operator[](size_t);

    const T& operator[](size_t) const;

    constexpr size_t getSize() const;

    constexpr bool isEmpty() const;

    Iterator begin();

    Iterator end();

    ConstIterator begin() const;

    ConstIterator end() const;

private:
    T arr[S]{};
};

template <typename T, size_t S>
T& Array<T, S>::operator[](size_t index) {
    return arr[index];
}

template <typename T, size_t S>
inline const T& Array<T, S>::operator[](size_t index) const {
    return arr[index];
}

template <typename T, size_t S>
constexpr size_t Array<T, S>::getSize() const {
    return S;
}

template <typename T, size_t S>
inline constexpr bool Array<T, S>::isEmpty() const {
    return S == 0;
}

template <typename T, size_t S>
inline ArrayIterator<T> Array<T, S>::begin() {
    return Iterator(arr);
}

template <typename T, size_t S>
inline ArrayIterator<T> Array<T, S>::end() {
    return Iterator(arr + S);
}

template <typename T, size_t S>
inline ArrayIterator<const T> Array<T, S>::begin() const {
    return ConstIterator(arr);
}

template <typename T, size_t S>
inline ArrayIterator<const T> Array<T, S>::end() const {
    return ConstIterator(arr + S);
}

#endif
