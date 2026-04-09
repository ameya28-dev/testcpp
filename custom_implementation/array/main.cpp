#include "array.h"
#include <algorithm>
#include <iostream>

template <typename T, size_t S>
std::ostream& operator<<(std::ostream& out, const Array<T, S>& arr) {
    out << '[';
    if (!arr.isEmpty()) {
        out << *arr.begin();
        std::for_each(++(arr.begin()), arr.end(), [&](const T t) { out << ", " << t; });
    }
    return out << ']';
}

int main() {
    Array<int, 5> arr;
    arr[4] = 7;
    std::cout << arr.getSize() << std::endl;
    std::cout << arr << '\n';
}
