#include <charconv>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string_view>
#include <system_error>
#include <type_traits>


constexpr size_t bufferSize = 8;

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void showToChars(T value, int base = 10) {
    char buffer[bufferSize]{};
    auto [ptr, err] = std::to_chars(buffer, buffer + bufferSize, value, base);
    if (err == std::errc()) {
        std::string_view str(buffer, ptr - buffer);
        std::cout << std::quoted(str) << '\n';
    } else {
        std::cerr << std::make_error_code(err).message() << std::endl;
    }
}

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
void showToChars(T value) {
    char buffer[bufferSize]{};
    auto [ptr, err] = std::to_chars(buffer, buffer + bufferSize, value);
    if (err == std::errc()) {
        std::string_view str(buffer, ptr - buffer);
        std::cout << std::quoted(str) << '\n';
    } else {
        std::cerr << std::make_error_code(err).message() << std::endl;
    }
}

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
void showToChars(T value, std::chars_format fmt) {
    char buffer[bufferSize]{};
    auto [ptr, err] = std::to_chars(buffer, buffer + bufferSize, value, fmt);
    if (err == std::errc()) {
        std::string_view str(buffer, ptr - buffer);
        std::cout << std::quoted(str) << '\n';
    } else {
        std::cerr << std::make_error_code(err).message() << std::endl;
    }
}

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
void showToChars(T value, std::chars_format fmt, int precision) {
    char buffer[bufferSize]{};
    auto [ptr, err] = std::to_chars(buffer, buffer + bufferSize, value, fmt, precision);
    if (err == std::errc()) {
        std::string_view str(buffer, ptr - buffer);
        std::cout << std::quoted(str) << '\n';
    } else {
        std::cerr << std::make_error_code(err).message() << std::endl;
    }
}

int main() {
    showToChars(42);
    showToChars(3.14);
    showToChars(-3.14159, std::chars_format::fixed);
    showToChars(-3.14159, std::chars_format::scientific);
    showToChars(-3.14159, std::chars_format::fixed, 3);
    showToChars(3.1415926535, std::chars_format::scientific, 10);
}
