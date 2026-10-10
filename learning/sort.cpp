#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
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

static bool caseInsensitiveLessThan(const std::string& str1, const std::string& str2) {
    std::size_t l1     = str1.length();
    std::size_t l2     = str2.length();
    std::size_t minLen = l1 < l2 ? l1 : l2;

    for (std::size_t i = 0; i < minLen; i++) {
        unsigned char c1 = static_cast<unsigned char>(str1[i]);
        unsigned char c2 = static_cast<unsigned char>(str2[i]);

        auto low1 = (c1 >= 'A' && c1 <= 'Z') ? (c1 + 32) : c1;
        auto low2 = (c2 >= 'A' && c2 <= 'Z') ? (c2 + 32) : c2;
        if (low1 != low2) {
            return low1 < low2;
        }
    }

    return l1 < l2;
}

struct Student {
    std::string name;
    int age;

    bool operator<(const Student& other) const {
        if (age != other.age) {
            return age < other.age;
        }
        return caseInsensitiveLessThan(name, other.name);
    }

    friend std::ostream& operator<<(std::ostream& out, const Student& stu) {
        return out << "{" << stu.name << ", " << stu.age << "}";
    }
};

int main() {
    std::vector<Student> vec{
        {"Kara Danvers", 24},
        {"James Olsen", 30},
        {"Alex Danvers", 26},
        {"Winslow Schott Jr.", 25},
        {R"(J'onn J'onzz)", 321},
        {"Cat Grant", 43},
        {"Mike Matthews", 30},
        {"Maggie Sawyer", 28},
        {"Lena Luthor", 22},
    };

    std::sort(vec.begin(), vec.end());

    std::cout << vec << '\n';
}
