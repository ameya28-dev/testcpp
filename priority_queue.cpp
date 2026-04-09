#include <iostream>
#include <queue>
#include <string_view>
#include <vector>

template <typename T>
void println(std::string_view rem, const T& v) {
    std::cout << rem << ": ";
    for (const auto& e : v) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void pop_println(std::string_view rem, T& pq) {
    std::cout << rem << ": ";
    for (; !pq.empty(); pq.pop()) {
        std::cout << pq.top() << ' ';
    }
    std::cout << '\n';
}

int main() {
    const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    println("data: ", data);

    std::priority_queue<int> max_priority_queue;
    for (int n : data) {
        max_priority_queue.push(n);
    }
    pop_println("max priority queue: ", max_priority_queue);

    std::priority_queue<int, std::vector<int>, std::greater<int>>
        min_priority_queue_1(data.begin(), data.end());
    pop_println("min priority queue 1: ", min_priority_queue_1);

    /// std::greater => lhs > rhs => greater value comes at the end of the list
    std::priority_queue min_priority_queue_2(data.begin(), data.end(),
                                             std::greater<int>());
    pop_println("min priority queue 2: ", min_priority_queue_2);

    struct {
        bool operator()(const int l, const int r) const { return l < r; }
    } customLess;
    std::priority_queue custom_priority_queue(data.begin(), data.end(),
                                              customLess);
    pop_println("custom priority queue: ", custom_priority_queue);

    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)>
        lambda_priority_queue(cmp);
    for (int n : data) {
        lambda_priority_queue.push(n);
    }
    pop_println("lambda priority queue: ", lambda_priority_queue);
}