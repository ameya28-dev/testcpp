#pragma once
#include <cstddef>
#include <cstdlib>

template <typename Vector>
class VectorIterator {
   public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

   private:
    PointerType m_ptr;

   public:
    VectorIterator(PointerType ptr) : m_ptr(ptr) {}

    VectorIterator& operator++() {
        m_ptr++;
        return *this;
    }

    VectorIterator operator++(int) {
        VectorIterator<Vector> iterator = *this;
        ++(*this);
        return iterator;
    }

    VectorIterator& operator--() {
        m_ptr--;
        return *this;
    }

    VectorIterator operator--(int) {
        VectorIterator<Vector> iterator = *this;
        --(*this);
        return iterator;
    }

    ReferenceType operator[](size_t index) {
        return *(m_ptr + index);
    }

    PointerType operator->() {
        return m_ptr;
    }

    ReferenceType operator*() {
        return *m_ptr;
    }

    bool operator==(const VectorIterator& other) const {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const VectorIterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class Vector {
   public:
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>;

   public:
    Vector();
    ~Vector();
    void PushBack(const T&);
    void PushBack(T&&);
    void PopBack();
    void Clear();
    Iterator begin() {
        return Iterator(m_data);
    }
    Iterator end() {
        return Iterator(m_data + m_size);
    }

    template <typename... Args>
    T& EmplaceBack(Args&&... args);

    size_t GetSize() const;
    T& operator[](size_t);
    const T& operator[](size_t) const;

   private:
    T* m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
    void _realloc(size_t);
};

template <typename T>
inline Vector<T>::Vector() {
    _realloc(2);
}

template <typename T>
inline Vector<T>::~Vector() {
    Clear();
    ::operator delete(m_data, m_capacity * sizeof(T));
}

template <typename T>
inline void Vector<T>::PushBack(const T& value) {
    if (m_size >= m_capacity) {
        _realloc(m_capacity + m_capacity / 2);
    }

    m_data[m_size] = value;
    m_size++;
}

template <typename T>
inline void Vector<T>::PushBack(T&& value) {
    if (m_size >= m_capacity) {
        _realloc(m_capacity + m_capacity / 2);
    }

    m_data[m_size] = std::move(value);
    m_size++;
}

template <typename T>
inline void Vector<T>::PopBack() {
    if (m_size > 0) {
        m_size--;
        m_data[m_size].~T();
    }
}

template <typename T>
inline void Vector<T>::Clear() {
    for (size_t i = 0; i < m_size; i++) {
        m_data[i].~T();
    }
    m_size = 0;
}

template <typename T>
inline size_t Vector<T>::GetSize() const {
    return m_size;
}

template <typename T>
inline T& Vector<T>::operator[](size_t index) {
    return m_data[index];
}

template <typename T>
inline const T& Vector<T>::operator[](size_t index) const {
    return m_data[index];
}

template <typename T>
inline void Vector<T>::_realloc(size_t new_capacity) {
    // 1. allocate a new block of memory
    // 2. copy/move old elements into new block
    // 3. delete

    T* new_block = (T*)::operator new(new_capacity * sizeof(T));

    if (new_capacity < m_size) {
        m_size = new_capacity;
    }

    for (size_t i = 0; i < m_size; i++) {
        new (&new_block[i]) T(std::move(m_data[i]));
    }

    for (size_t i = 0; i < m_size; i++) {
        m_data[i].~T();
    }

    ::operator delete(m_data, m_capacity * sizeof(T));
    m_data = new_block;
    m_capacity = new_capacity;
}

template <typename T>
template <typename... Args>
inline T& Vector<T>::EmplaceBack(Args&&... args) {
    if (m_size >= m_capacity) {
        _realloc(m_capacity + m_capacity / 2);
    }

    new (&m_data[m_size]) T(std::forward<Args>(args)...);

    // m_data[m_size] = T(std::forward<Args>(args)...);
    return m_data[m_size++];
}