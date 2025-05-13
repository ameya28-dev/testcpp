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
    T* m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 2;

    void re_alloc(size_t new_capacity);
};

template <typename T>
inline Vector<T>::Vector() { re_alloc(2); }

template <typename T>
inline void Vector<T>::re_alloc(size_t new_capacity) {
    T* new_block = new T[new_capacity];

    if (m_size > new_capacity) m_size = new_capacity;
    for (int i = 0; i < m_size; i++) new_block[i] = m_data[i];

    delete[] m_data;
    m_data = new_block;
    m_capacity = new_capacity;
}

template <typename T>
inline void Vector<T>::push_back(const T& value) {
    if (m_size >= m_capacity) re_alloc(m_capacity + m_capacity / 2);
    m_data[m_size] = value;
    m_size++;
}

template <typename T>
inline size_t Vector<T>::size() const {
    return m_size;
}

template <typename T>
inline const T& Vector<T>::operator[](size_t index) const {
    return m_data[index];
}

template <typename T>
inline T& Vector<T>::operator[](size_t index) {
    return m_data[index];
}
