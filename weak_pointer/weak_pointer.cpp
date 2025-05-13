#include <iostream>
#include <memory>

struct Object {
    ~Object() { std::cout << "Deleted Object\n"; }
};

struct Manager {
    std::weak_ptr<Object> Obj;

    void Func() {
        if (std::shared_ptr<Object> obj = Obj.lock()) {
            // obj->
        }

        if (Obj.expired()) {
        }

        std::cout << Obj.use_count() << std::endl;
    }
};

Manager manager;

int main() {
    {
        std::shared_ptr<Object> obj = std::make_shared<Object>();
        manager.Obj = obj;
        manager.Func();
    }
    
    manager.Func();
    // std::cout << manager.Obj << std::endl;
}