#include <algorithm>
#include <iostream>
#include <vector>

static size_t size = 0;

void* operator new(size_t s) {
    size += s;

    void* p = malloc(s);
    return p;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    if (vec.empty()) {
        return out << "{}";
    }
    out << "std::vector<int>{ " << *vec.begin();
    std::for_each(std::next(vec.begin()), vec.end(), [&out](const int& element) {
        out << ", " << element;
    });
    return out << " }";
}

int main() {
    std::vector<int> v1{1, 2, 4, 5, 7};
    std::vector<int> v2{2, 4, 5};
    std::vector<int> v(std::min(v1.size(), v2.size()));

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
    std::cout << v << std::endl;
    std::cout << "Allocated " << size << " bytes\n";
}