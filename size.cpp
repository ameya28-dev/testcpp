#include <cstddef>


// size_t
// #ifdef _WIN64
// __MINGW_EXTENSION typedef unsigned __int64 size_t;
// #else
// typedef unsigned int size_t;

// std::size_t
// #ifndef __SIZE_TYPE__
// #ifdef _WIN64
// #define __SIZE_TYPE__ long long unsigned int
// #else
// #define __SIZE_TYPE__ long unsigned int
// #endif
// #endif

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::size_t sum = 0;
    for (size_t i = 0; i < 5; i++) {
        sum += i;
    }
}