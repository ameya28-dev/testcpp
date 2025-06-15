#include <iostream>

class Log {
   public:
    inline static int x = 15;
};

// int Log::x = 15;

int main() {
    // Log::x = 10;
    std::cout << Log::x << std::endl;
}