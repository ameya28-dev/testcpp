#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <variant>

enum class Color { red,
                   green,
                   yellow };

std::ostream& operator<<(std::ostream& instream, const Color& color) {
    switch (color) {
        case Color::red:
            instream << "red";
            break;
        case Color::yellow:
            instream << "yellow";
            break;
        case Color::green:
            instream << "green";
            break;
        default:
            instream << "";
    }
    return instream;
}

std::variant<int, std::string, Color> get_random() {
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> uniform(1, 9);

    int random_number = uniform(engine);
    std::cout << "Random number: " << random_number << std::endl;

    if (random_number < 4) {
        return random_number;
    }

    if (random_number < 7) {
        std::stringstream ss;
        ss << "Number: ";
        ss << random_number;

        return ss.str();
    }

    if (random_number == 7) return Color::red;
    if (random_number == 8) return Color::yellow;
    if (random_number == 9) return Color::green;

    return "";
}

int main() {
    auto result = get_random();

    if (const auto it = std::get_if<int>(&result)) {
        std::cout << *it << std::endl;
    }

    if (const auto it = std::get_if<std::string>(&result)) {
        std::cout << *it << std::endl;
    }

    if (const auto it = std::get_if<Color>(&result)) {
        std::cout << *it << std::endl;
    }
}