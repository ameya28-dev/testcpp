#include <array>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    out << "[";
    if (!vec.empty()) {
        out << *vec.cbegin();
        for (auto it = vec.cbegin() + 1; it != vec.cend(); ++it) {
            out << ", " << *it;
        }
    }
    return out << "]";
}

constexpr std::array<std::pair<int, const char*>, 4> map = {{
    {2, "foo"},
    {3, "fizz"},
    {5, "buzz"},
    {7, "baz"},
}};

std::string _getFizzBuzzValue(size_t index) {
    std::string str;
    for (const auto [key, value] : map) {
        if ((index + 1) % key == 0) {
            str += value;
        }
    }

    if (str.empty()) {
        char buffer[16];
        auto res = std::to_chars(buffer, buffer + sizeof(buffer), index + 1);
        if (res.ec == std::errc()) {
            std::string result(buffer, res.ptr - buffer);
            return result;
        } else {
            std::cerr << std::make_error_code(res.ec).message() << std::endl;
        }
        return std::to_string(index + 1);
    } else {
        return str;
    }
}

std::vector<std::string> _getFizzBuzzList(size_t s) {
    std::vector<std::string> res(s);

    for (size_t i = 0; i < s; i++) {
        res[i] = _getFizzBuzzValue(i);
    }

    return res;
}

int main() {
    auto result = _getFizzBuzzList(210);
    std::cout << result << '\n';
}
