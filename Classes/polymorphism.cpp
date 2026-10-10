#include <mutex>
#include <utility>

struct Shape {};

struct Circle : Shape {
    float radius;
};

struct Rectangle : Shape {
    float length, breadth;
};

struct Triangle : Shape {
    float a, b, c;
};

Shape createCircle(float radius) {
    return Circle {
        radius
    }
}

struct FreeDeleter {
    void operator()(int* ptr) {
        // Does cleaning stuff
    }
};

struct unique_ptr<int> : private FreeDeleter {
    // others functions and memebers

    
public:
    ~unique_ptr() {
        operator()(ptr);
    }

private:
    int* ptr;
};
