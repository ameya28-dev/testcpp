#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <string_view>
#include <type_traits>
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

template <typename T, typename Compare = std::less<T>>
class VPriorityQueue : public std::priority_queue<T, std::vector<T>, Compare> {
public:
    using std::priority_queue<T, std::vector<T>, Compare>::priority_queue;

    friend std::ostream& operator<<(std::ostream& out, const VPriorityQueue& pq) {
        const auto& v = pq.c;
        out << '[';
        if (!v.empty()) {
            out << *v.begin();
            std::for_each(std::next(v.begin()), v.end(), [&](const T& t) { out << ", " << t; });
        }
        return out << "]";
    }
};

int main() {
    const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    println("data: ", data);
    std::cout << "Is 'data' initializer_list: " << std::boolalpha
              << (std::is_same_v<decltype(data), std::initializer_list<int>>) << '\n';

    std::priority_queue<int> max_priority_queue;
    for (int n : data) {
        max_priority_queue.push(n);
    }
    pop_println("max priority queue: ", max_priority_queue);

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_priority_queue_1(data.begin(), data.end());
    pop_println("min priority queue 1: ", min_priority_queue_1);

    /// std::greater => lhs > rhs => greater value comes at the end of the list
    std::priority_queue min_priority_queue_2(data.begin(), data.end(), std::greater<int>());
    pop_println("min priority queue 2: ", min_priority_queue_2);

    struct {
        bool operator()(const int l, const int r) const {
            return l < r;
        }
    } customLess;

    std::priority_queue custom_priority_queue(data.begin(), data.end(), customLess);
    pop_println("custom priority queue: ", custom_priority_queue);

    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> lambda_priority_queue(cmp);
    for (int n : data) {
        lambda_priority_queue.push(n);
    }
    pop_println("lambda priority queue: ", lambda_priority_queue);

    VPriorityQueue<int, std::less<int>> vq(data.begin(), data.end());
}
