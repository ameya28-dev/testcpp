#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

struct error {
    std::string message;

    error(std::string message) : message(message) {}
};

std::tuple<std::string, int> getPerson() {
    return {"Ameya", 25};
}

std::variant<error, std::vector<std::string>> file_content(const std::string& file_name) {
    if (!std::filesystem::exists(file_name)) {
        return error("File does not exist");
    }

    std::ifstream file(file_name);
    std::vector<std::string> res(20);
    if (!file.is_open()) {
        return error("File could not be opened");
    }

    std::string line;
    while (std::getline(file, line)) {
        res.emplace_back(line);
    }

    if (file.bad()) {
        return error("I/O error while reading");
    }

    if (file.eof()) {
        return res;
    }

    if (file.fail()) {
        return error("I/O reading failed due to bad character");
    }

    return error("Unknown error occured");
}

const std::unordered_map<int, std::string> createMap() {
    std::unordered_map<int, std::string> map{{1, "First"}, {2, "Second"}, {3, "Third"}};
    return map;
}

void display_variant(std::variant<std::string, int>& v) {
    if (const int* ptr = std::get_if<int>(&v)) {
        std::cout << "Saved as int:\t" << *ptr << '\n';
    } else {
        std::cout << "Saved as string:\t" << std::get<std::string>(v) << '\n';
    }
}

std::ostream& operator<<(std::ostream& instream, const std::vector<std::string>& vec) {
    for (auto& s : vec) {
        instream << s << '\n';
    }
    return instream;
}

int main() {
    std::variant<std::string, int> v{10};
    display_variant(v);
    v = "Ameya";
    display_variant(v);

    auto [name, age] = getPerson();

    std::cout << name << ":\t" << age << '\n';

    for (auto [key, value] : createMap()) {
        std::cout << "Key:\t" << key << "\tValue:\t" << value << '\n';
    }

    std::cout << "Please enter file name:\n";
    std::string file_name;

    std::cin >> file_name;

    auto result = file_content(file_name);
    if (const auto ptr = std::get_if<std::vector<std::string>>(&result)) {
        std::cout << *ptr << '\n';
    } else {
        std::cout << std::get<error>(result).message << '\n';
    }
}
