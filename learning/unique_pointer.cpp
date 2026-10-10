#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

template <class T>
class unique_ptr {
public:
    unique_ptr() noexcept : unique_ptr{nullptr} {}

    explicit unique_ptr(T* ptr) noexcept : _ptr{ptr} {}

    unique_ptr(const unique_ptr&)            = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& other) noexcept : _ptr{other.release()} {}

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset(other.release());
        }
        return *this;
    }

    explicit operator bool() const noexcept {
        return static_cast<bool>(_ptr);
    }

    T* get() const noexcept {
        return _ptr;
    }

    T* operator->() const noexcept {
        return _ptr;
    }

    T& operator*() const noexcept {
        return *_ptr;
    }

    T* release() noexcept {
        return std::exchange(_ptr, nullptr);
        // T* old = m_ptr;
        // m_ptr = nullptr;
        // return old;
    }

    void reset(T* ptr = nullptr) noexcept {
        // T* old = m_ptr;
        // m_ptr = ptr;
        T* old = std::exchange(_ptr, ptr);
        if (old) {
            delete old;
        }
    }

    ~unique_ptr() noexcept {
        if (_ptr) {
            delete _ptr;
        }
    }

private:
    T* _ptr;
};

template <class T, class... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct Person {
public:
    Person(const std::string& name, int age) : name(name), age(age) {}

    const std::string& get_name() const {
        return name;
    }

    const int get_age() const {
        return age;
    }

private:
    std::string name;
    int age;
};

std::ostream& operator<<(std::ostream& stream, const Person& person) {
    stream << "Person{name: " << person.get_name() << ", age: " << person.get_age() << "}";
    return stream;
}

template <typename T>
void printUnique(std::unique_ptr<T> ptr) {
    std::cout << sizeof(ptr) << '\n';
}

int main() {
    auto ptr = make_unique<Person>("Ameya", 25);
    std::cout << "Name: " << ptr->get_name() << std::endl;
    std::cout << "Age: " << ptr->get_age() << std::endl;
    std::cout << *ptr.get() << std::endl;

    auto u    = std::make_unique<int>(4);
    auto& ref = u;
    std::cout << u.get() << '\t' << *u << '\n';
    std::cout << ref.get() << '\t' << *ref << '\n';

    struct S {
        int a;
        float b;

        S(int a, float b) : a(a), b(b) {}
    };

    auto v = std::make_unique<S>(3, 4.0f);
    printUnique(std::move(v));
    // std::cout << v->a << '\t' << v->b << '\n';
    {
        struct FreeDeleter {
            void operator()(int* ptr) {
                free(ptr);
            }
        };

        using Allocater    = std::unique_ptr<int, FreeDeleter>;
        auto makeAllocater = [](int size = 1) { return Allocater{static_cast<int*>(malloc(sizeof(int) * size))}; };
        auto alloc         = makeAllocater();
        *alloc = 1;
        std::cout << *alloc << '\n';
    }

    return 0;
}
