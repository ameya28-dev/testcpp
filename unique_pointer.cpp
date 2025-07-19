#include <iostream>
#include <string>
#include <utility>

template <class T>
class unique_ptr {
   public:
    unique_ptr() noexcept : unique_ptr{nullptr} {}
    explicit unique_ptr(T *ptr) noexcept : m_ptr{ptr} {}

    unique_ptr(const unique_ptr &) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr(unique_ptr &&other) noexcept : m_ptr{other.release()} {}

    unique_ptr &operator=(unique_ptr &&other) noexcept {
        if (this != &other) {
            reset(other.release());
        }
        return *this;
    }

    explicit operator bool() const noexcept {
        return static_cast<bool>(m_ptr);
    }

    T *get() const noexcept { return m_ptr; }

    T *operator->() const noexcept { return m_ptr; }

    T &operator*() const noexcept { return *m_ptr; }

    T *release() noexcept {
        return std::exchange(m_ptr, nullptr);
        // T* old = m_ptr;
        // m_ptr = nullptr;
        // return old;
    }

    void reset(T *ptr = nullptr) noexcept {
        // T* old = m_ptr;
        // m_ptr = ptr;
        T *old = std::exchange(m_ptr, ptr);
        if (old) {
            delete old;
        }
    }

    ~unique_ptr() noexcept {
        if (m_ptr) {
            delete m_ptr;
        }
    }

   private:
    T *m_ptr;
};

template <class T, class... Args>
unique_ptr<T> make_unique(Args &&...args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct Person {
   public:
    Person(const std::string &name, int age) : name(name), age(age) {}

    const std::string &get_name() const { return name; }

    const int get_age() const { return age; }

   private:
    std::string name;
    int age;
};

std::ostream &operator<<(std::ostream &stream, const Person &person) {
    stream << "Person{name: " << person.get_name() << ", age: " << person.get_age() << "}";
    return stream;
}

int main() {
    auto ptr = make_unique<Person>("Ameya", 25);
    std::cout << "Name: " << ptr->get_name() << std::endl;
    std::cout << "Age: " << ptr->get_age() << std::endl;
    std::cout << *ptr.get() << std::endl;

    return 0;
}