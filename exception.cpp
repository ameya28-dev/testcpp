#include <iostream>
#include <stdexcept>

int main() {
    try {
        throw 101;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (...) {
        std::exception_ptr ptr = std::current_exception();
        if (ptr) {
            auto p = ptr.__cxa_exception_type();
            auto name = p->name();
            std::cout << name << std::endl;
        }
    }
}