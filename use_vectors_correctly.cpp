#include <algorithm>
#include <iostream>
#include <print>
#include <set>
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

std::vector<int> find_set_intersection(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::set<int> s1(v1.begin(), v1.end());
    std::set<int> s2(v2.begin(), v2.end());

    std::vector<int> result;
    result.reserve(std::min(v1.size(), s2.size()));

    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(result));
    return result;
}

int main() {
    {
        std::vector<int> v1{1, 2, 4, 5, 7};
        std::vector<int> v2{2, 0, 8, 2, 2, 1};

        auto result = find_set_intersection(v1, v2);
        std::cout << result << '\n';
        std::cout << "size of result = " << result.size() << '\n';
        std::cout << "size of capacity = " << result.capacity() << '\n';
    }

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
        std::cout << *v.data() << '\n';
        std::cout << *(v.data() + 1) << '\n';
        std::cout << *(v.data() + 2) << '\n';
        std::cout << *(v.data() + v.size() - 1) << '\n';
    }
}