#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

void print(std::string_view text, const std::vector<int>& v = {}) {
    std::cout << text << ": ";
    for (const auto& e : v) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}

void print(std::string_view text, bool check) {
    std::cout << text << ": ";
    std::cout << std::boolalpha << check << '\n';
}

int main() {
    print("Max Heap");

    std::vector<int> v{3, 2, 4, 1, 5, 9};
    print("initially, v", v);
    print("is v a heap", std::is_heap(v.begin(), v.end()));

    std::make_heap(v.begin(), v.end());
    print("after make_heap, v", v);
    print("is v a heap", std::is_heap(v.begin(), v.end()));

    std::pop_heap(v.begin(), v.end());
    print("after pop_heap, v", v);

    auto top = v.back();
    v.pop_back();
    print("former top element", std::vector<int>{top});
    print("after removing the former top element, v", v);

    print("Messing up heap");
    v.push_back(10);
    v.push_back(11);
    print("is v a heap", std::is_heap(v.begin(), v.end()));
    auto it = std::is_heap_until(v.begin(), v.end());
    print("v is heap until index", std::vector<int>{(int) std::distance(v.begin(), it) - 1});
    print("Fixing heap");
    std::push_heap(v.begin(), std::next(v.end(), -1));
    std::push_heap(v.begin(), v.end());
    print("is v a heap", std::is_heap(v.begin(), v.end()));
    print("after fixing, v", v);

    std::vector<int> v1{3, 2, 4, 1, 5, 9};
    print("initially, v1", v1);
    print("is v1 a heap", std::is_heap(v1.begin(), v1.end()));

    std::make_heap(v1.begin(), v1.end(), std::greater<int>());
    print("after make_heap, v1", v1);
    print("is v1 a heap", std::is_heap(v1.begin(), v1.end()));
    print("is v1 a MIN heap", std::is_heap(v1.begin(), v1.end(), std::greater<int>()));

    std::pop_heap(v1.begin(), v1.end(), std::greater<int>());
    print("after pop_heap, v1", v1);

    auto top1 = v1.back();
    v1.pop_back();
    print("former top element", std::vector<int>{top1});
    print("after removing the former top element, v1", v1);
}
