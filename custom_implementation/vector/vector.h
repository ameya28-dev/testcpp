#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <cstdlib>
#include <iterator>

template <typename T>
class VectorIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

public:
    VectorIterator(pointer ptr) : _ptr(ptr) {}

    VectorIterator& operator++() {
        _ptr++;
        return *this;
    }

    VectorIterator operator++(int) {
        auto iterator = *this;
        ++(*this);
        return iterator;
    }

    VectorIterator& operator--() {
        _ptr--;
        return *this;
    }

    VectorIterator operator--(int) {
        VectorIterator<T> iterator = *this;
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

    bool operator==(const VectorIterator& other) const {
        return _ptr == other._ptr;
    }

    bool operator!=(const VectorIterator& other) const {
        return !(*this == other);
    }

    VectorIterator operator+=(difference_type n) {
        _ptr += n;
        return *this;
    }

    VectorIterator operator-=(difference_type n) {
        _ptr -= n;
        return *this;
    }

private:
    pointer _ptr;
};

template <typename T>
class Vector {
public:
    using ValueType     = T;
    using Iterator      = VectorIterator<T>;
    using ConstIterator = VectorIterator<const T>;

public:
    Vector() {
        _realloc(2);
    }

    ~Vector();

    void PushBack(const T&);

    void PushBack(T&&);

    void PopBack();

    void Clear();

    bool IsEmpty() const {
        return _size == 0;
    }

    Iterator begin() {
        return Iterator(_data);
    }

    Iterator end() {
        return Iterator(_data + _size);
    }

    ConstIterator begin() const {
        return ConstIterator(_data);
    }

    ConstIterator end() const {
        return ConstIterator(_data + _size);
    }

    template <typename... Args>
    T& EmplaceBack(Args&&... args);

    size_t GetSize() const;

    T& operator[](size_t);

    const T& operator[](size_t) const;

private:
    void _realloc(size_t);

private:
    T* _data         = nullptr;
    size_t _size     = 0;
    size_t _capacity = 0;
};

template <typename T>
inline Vector<T>::~Vector() {
    Clear();
    ::operator delete(_data, _capacity * sizeof(T));
}

template <typename T>
inline void Vector<T>::PushBack(const T& value) {
    if (_size >= _capacity) {
        _realloc(_capacity + _capacity / 2);
    }

    _data[_size] = value;
    _size++;
}

template <typename T>
inline void Vector<T>::PushBack(T&& value) {
    if (_size >= _capacity) {
        _realloc(_capacity + _capacity / 2);
    }

    _data[_size] = std::move(value);
    _size++;
}

template <typename T>
inline void Vector<T>::PopBack() {
    if (_size > 0) {
        _size--;
        _data[_size].~T();
    }
}

template <typename T>
inline void Vector<T>::Clear() {
    for (size_t i = 0; i < _size; i++) {
        _data[i].~T();
    }
    _size = 0;
}

template <typename T>
inline size_t Vector<T>::GetSize() const {
    return _size;
}

template <typename T>
inline T& Vector<T>::operator[](size_t index) {
    return _data[index];
}

template <typename T>
inline const T& Vector<T>::operator[](size_t index) const {
    return _data[index];
}

template <typename T>
inline void Vector<T>::_realloc(size_t new_capacity) {
    // 1. allocate a new block of memory
    // 2. copy/move old elements into new block
    // 3. delete

    T* new_block = (T*) ::operator new(new_capacity * sizeof(T));

    if (new_capacity < _size) {
        _size = new_capacity;
    }

    for (size_t i = 0; i < _size; i++) {
        new (&new_block[i]) T(std::move(_data[i]));
    }

    for (size_t i = 0; i < _size; i++) {
        _data[i].~T();
    }

    ::operator delete(_data, _capacity * sizeof(T));
    _data     = new_block;
    _capacity = new_capacity;
}

template <typename T>
template <typename... Args>
inline T& Vector<T>::EmplaceBack(Args&&... args) {
    if (_size >= _capacity) {
        _realloc(_capacity + _capacity / 2);
    }

    new (&_data[_size]) T(std::forward<Args>(args)...);

    // _data[_size] = T(std::forward<Args>(args)...);
    return _data[_size++];
}

#endif
