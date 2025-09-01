#include <algorithm>
#include <iostream>
#include <print>
#include <vector>

static size_t size = 0;
static size_t copies = 0;
static size_t moves = 0;

void* operator new(size_t s) {
    size += s;

    void* p = malloc(s);
    return p;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    if (vec.empty()) {
        return out << "{}";
    }
    out << "std::vector<" << typeid(T).name() << ">{ " << *vec.begin();
    std::for_each(std::next(vec.begin()), vec.end(), [&out](const T& element) {
        out << ", " << element;
    });
    return out << " }";
}

struct entity {
    entity(int val) : data(val) {}

    entity(const entity& val) : data(val.data) {
        copies++;
    }

    entity(const entity&& val) : data(val.data) {
        moves++;
    }

    friend std::ostream& operator<<(std::ostream& instream, const entity& val) {
        return instream << "entity{data:" << val.data << "}";
    }

   private:
    int data;
};

int main() {
    std::vector<int> v1{1, 2, 4, 5, 7};
    std::vector<int> v2{2, 4, 5};
    std::vector<int> v;
    v.reserve(1);
    // v.resize(1);

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));
    // std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::begin(v));
    std::cout << v << std::endl;
    std::cout << "Allocated " << size << " bytes\n";
    std::cout << "Size of v:" << v.size() << '\n';
    std::cout << "Capacity of v:" << v.capacity() << '\n';

    {
        size = 0;

        std::vector<entity> v;
        v.reserve(3);

        v.emplace_back(1);
        v.emplace_back(2);
        v.emplace_back(3);

        std::cout << "Allocated " << size << " bytes\n";
        std::cout << "Copies:  " << copies << " \n";
        std::cout << "Moves:  " << moves << " \n";

        std::cout << v << "\n";
    }
}