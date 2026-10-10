#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <cstddef>
#include <iterator>
#include <utility>

constexpr std::size_t defaultBuffer = 2;

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

    reference operator[](std::size_t index) {
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
    using ValueType            = T;
    using Iterator             = VectorIterator<T>;
    using ConstIterator        = VectorIterator<const T>;
    using ReverseIterator      = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

public:
    Vector() {
        _reallocate(defaultBuffer);
    }

    ~Vector() {
        Clear();
        ::operator delete(_data, _capacity * sizeof(T));
    }

    void PushBack(const T& value) {
        if (_size >= _capacity) {
            _reallocate(_resizeStrategy(_capacity));
        }

        _data[_size] = value;
        _size++;
    }

    void PushBack(T&& value) {
        if (_size >= _capacity) {
            _reallocate(_resizeStrategy(_capacity));
        }

        _data[_size] = std::move(value);
        _size++;
    }

    void PopBack() {
        if (_size > 0) {
            _size--;
            _data[_size].~T();
        }
    }

    void Clear() {
        for (std::size_t i = 0; i < _size; i++) {
            _data[i].~T();
        }
        _size = 0;
    }

    bool IsEmpty() const noexcept {
        return _size == 0;
    }

    Iterator begin() noexcept {
        return Iterator(_data);
    }

    Iterator end() noexcept {
        return Iterator(_data + _size);
    }

    ConstIterator begin() const noexcept {
        return ConstIterator(_data);
    }

    ConstIterator end() const noexcept {
        return ConstIterator(_data + _size);
    }

    ReverseIterator rbegin() noexcept {
        return ReverseIterator(end());
    }

    ReverseIterator rend() noexcept {
        return ReverseIterator(begin());
    }

    ConstReverseIterator rbegin() const noexcept {
        return ConstReverseIterator(end());
    }

    ConstReverseIterator rend() const noexcept {
        return ConstReverseIterator(begin());
    }

    template <typename... Args>
    T& EmplaceBack(Args&&... args) {
        if (_size >= _capacity) {
            _reallocate(_resizeStrategy(_capacity));
        }

        new (&_data[_size]) T(std::forward<Args>(args)...);

        return _data[_size++];
    }

    constexpr std::size_t GetSize() const {
        return _size;
    }

    T& operator[](std::size_t index) {
        return _data[index];
    }

    const T& operator[](std::size_t index) const {
        return _data[index];
    }


private:
    void _reallocate(std::size_t capacity) {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into new block
        // 3. delete

        T* new_block = (T*) ::operator new(capacity * sizeof(T));

        if (capacity < _size) {
            _size = capacity;
        }

        for (std::size_t i = 0; i < _size; i++) {
            new (&new_block[i]) T(std::move(_data[i]));
        }

        for (std::size_t i = 0; i < _size; i++) {
            _data[i].~T();
        }

        ::operator delete(_data, _capacity * sizeof(T));
        _data     = new_block;
        _capacity = capacity;
    }

    constexpr std::size_t _resizeStrategy(std::size_t curr) {
        return curr + curr / 2;
    }

private:
    T* _data              = nullptr;
    std::size_t _size     = 0;
    std::size_t _capacity = 0;
};


#endif