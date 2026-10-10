#include <ostream>
#include <utility>

// Printing a std type through an operator<< declared in the global namespace, before the header.
std::ostream& operator<<(std::ostream& stream, const std::pair<int, int>& pair) {
    return stream << '(' << pair.first << ", " << pair.second << ')';
}

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include "forward_list.hpp"
#include "forward_list_io.hpp"

// A generic "can I print this?" check, like the ones test frameworks and loggers use.
template <typename T, typename = void>
struct CanPrint : std::false_type {};

template <typename T>
struct CanPrint<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>> : std::true_type {
};

struct Point {
    int x, y;
}; // deliberately has no operator<<

static_assert(CanPrint<Forward::ForwardList<int>>::value);
static_assert(!CanPrint<Forward::ForwardList<Point>>::value);
static_assert(CanPrint<Forward::ForwardList<Forward::ForwardList<int>>>::value);
static_assert(!CanPrint<Forward::ForwardList<Forward::ForwardList<Point>>>::value);

int main() {
    using Forward::ForwardList;

    // Basic push / access
    ForwardList<int> numbers;
    assert(numbers.empty());
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_front(1);
    assert(numbers.size() == 3 && numbers.front() == 1 && numbers.back() == 3);
    std::cout << numbers << '\n';

    // Removing the tail must update back()
    assert(numbers.remove(3));
    assert(numbers.back() == 2);
    numbers.push_back(4);
    assert(to_string(numbers) == "forward list: 1->2->4->nullptr");

    // Removing head, middle, and the last remaining node
    assert(numbers.remove(1));
    assert(numbers.remove(4));
    assert(numbers.remove(2));
    assert(numbers.empty());
    numbers.push_back(5);
    assert(numbers.front() == 5 && numbers.back() == 5);

    // pop_front down to empty, then reuse
    numbers.push_back(6);
    numbers.pop_front();
    numbers.pop_front();
    assert(numbers.empty());
    numbers.push_front(7);
    assert(numbers.back() == 7);

    // Copy, move, assignment, equality
    ForwardList<std::string> words{"a", "b", "c"};
    ForwardList<std::string> copy = words;
    assert(copy == words);
    copy.push_back("d");
    assert(copy != words);

    ForwardList<std::string> moved = std::move(copy);
    assert(copy.empty() && moved.size() == 4);

    words = moved;
    assert(words == moved);
    ForwardList<std::string>& alias = words;
    words                           = alias; // self-assignment
    assert(words.size() == 4);
    words = std::move(moved);
    assert(words.size() == 4);

    // reverse keeps back() correct
    words.reverse();
    assert(to_string(words) == "forward list: d->c->b->a->nullptr");
    assert(words.back() == "a");
    words.push_back("z");
    assert(words.back() == "z");

    // Iterators: range-for, std algorithms, const iteration, mixed comparison
    for (std::string& word : words) {
        word += "!";
    }
    assert(words.front() == "d!" && words.contains("z!"));
    assert(std::find(words.begin(), words.end(), "b!") != words.end());

    const ForwardList<std::string>& const_words = words;
    std::size_t count                           = 0;
    for (const std::string& word : const_words) {
        count += word.size();
    }
    assert(count == 10);
    assert(words.begin() == words.cbegin());

    // emplace
    ForwardList<std::string> emplaced;
    emplaced.emplace_back(3, 'x');
    emplaced.emplace_front("hi");
    assert(to_string(emplaced) == "forward list: hi->xxx->nullptr");

    // remove reports failure instead of throwing
    ForwardList<int> empty_list;
    assert(!empty_list.remove(1));
    assert(!words.remove("missing"));

    // Lists of non-printable types are still fine to store and use
    ForwardList<Point> points{{1, 2}, {3, 4}};
    assert(points.size() == 2 && points.back().y == 4);

    // Nested lists print through the same constrained operator<<
    ForwardList<ForwardList<int>> nested{{1, 2}, {3}};
    assert(to_string(nested) == "forward list: forward list: 1->2->nullptr->forward list: 3->nullptr->nullptr");

    // Element printed through the global operator<< declared above
    ForwardList<std::pair<int, int>> pairs{{1, 2}, {3, 4}};
    assert(to_string(pairs) == "forward list: (1, 2)->(3, 4)->nullptr");

    std::cout << "all tests passed\n";
    return 0;
}
