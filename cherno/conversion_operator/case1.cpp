#include <iostream>
struct Orange {
    operator float() { return 5.5f; }
};

template <typename T>
class ScopedPtr {
   public:
    ScopedPtr() = default;
    ScopedPtr(T* ptr) : m_ptr(ptr) {}
    ~ScopedPtr() { delete m_ptr; }

    T* get() { return m_ptr; }
    const T* get() const { return m_ptr; }

    operator bool() const { return m_ptr != nullptr; }

   private:
    T* m_ptr = nullptr;
};

struct Entity {
    float x = 0.0f, y = 0.0f;
};

void process_entity(const ScopedPtr<Entity>& ptr) {
    if (ptr) {
    }
}

int main() {
    Orange orange;
    float v = orange;
    std::cout << v << std::endl;
    std::cout << (float)orange << std::endl;

    ScopedPtr<Entity> scope_ptr = new Entity();
    Entity* entity = new Entity();
}