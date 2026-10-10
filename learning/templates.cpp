#include <iostream>
#include <string>
#include <type_traits>

// template <typename T, typename = void>
// struct IsStreamable : std::false_type {};

// template <typename T>
// struct IsStreamable<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

template <typename T>
struct Failure {
    int status;
    T body;
};

template <typename T>
// , typename std::enable_if_t<IsStreamable<T>::value, std::ostream&>
std::ostream& operator<<(std::ostream& out, const Failure<T>& f) {
    return out << "Failure{status = " << f.status << ", body = " << f.body << "}";
}

int main() {
    auto f = Failure<std::string>{10, "ABDJCM"};
    std::cout << f << '\n';
}
