#include <algorithm>
#include <chrono>
#include <forward_list>
#include <iostream>
#include <vector>

#define LIST {8, 7, 5, 9, 0, 1, 3, 2, 6, 4, 10, 12, 11, 16, 14, 15, 20, 19, 18, 17, 21, 22, 16, 23, 24, 25}

std::ostream& operator<<(std::ostream& ostr, const std::forward_list<int>& list) {
    for (auto& i : list) ostr << i << '\t';
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const std::vector<int>& list) {
    for (auto& i : list) ostr << i << '\t';
    return ostr;
}

std::chrono::duration<double> test_forward_list() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    std::forward_list<int> list = LIST;
    list.sort();
    list.reverse();

    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

    return (end - start);
}

std::chrono::duration<double> test_vector() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    std::vector<int> list = LIST;
    std::sort(list.begin(), list.end());

    std::reverse(list.begin(), list.end());

    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

    return (end - start);
}

int main() {
    auto time1 = test_forward_list();
    auto time2 = test_vector();
    std::cout << "Duration for forward_list in micro seconds:\t" << time1.count() * 1000000 << std::endl;
    std::cout << "Duration for vector in micro seconds:\t" << time2.count() * 1000000 << std::endl;
}