#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

struct Coordinate {
    float lon, lat;
};

struct Weather {
    std::string main, description, icon;
    int id;
};

struct Main {
    float temp, feels_like, temp_min, temp_max;
    int pressure, humidity, sea_level, ground_level;
};

struct WeatherData {
    std::string base;
    Main main;
    std::vector<Weather> weather;
    Coordinate coordinate;
};

struct WeatherError {
    long status_code;
    std::string message;
};

struct IntWrapper {
    int i;
};

int main() {
    std::cout << "Size of char: " << sizeof(char) << "\n";
    std::cout << "Size of int: " << sizeof(int) << "\n";
    std::cout << "Size of long: " << sizeof(long) << "\n";
    std::cout << "Size of float: " << sizeof(float) << "\n";
    std::cout << "Size of double: " << sizeof(double) << "\n";
    std::cout << "Size of size_t: " << sizeof(size_t) << "\n";
    std::cout << "Size of std::string: " << sizeof(std::string) << "\n" << "\n";

    std::cout << "Alignment of char: " << std::alignment_of_v<char> << "\n";
    std::cout << "Alignment of int: " << std::alignment_of_v<int> << "\n";
    std::cout << "Alignment of long: " << std::alignment_of_v<long> << "\n";
    std::cout << "Alignment of float: " << std::alignment_of_v<float> << "\n";
    std::cout << "Alignment of double: " << std::alignment_of_v<double> << "\n";
    std::cout << "Alignment of size_t: " << std::alignment_of_v<size_t> << "\n";
    std::cout << "Alignment of std::string: "
              << std::alignment_of_v<std::string> << "\n"
              << "\n";

    std::cout << "Size of std::vector<char>: " << sizeof(std::vector<char>)
              << "\n";
    std::cout << "Size of std::vector<int>: " << sizeof(std::vector<int>)
              << "\n";
    std::cout << "Size of std::vector<float>: " << sizeof(std::vector<float>)
              << "\n";
    std::cout << "Size of std::vector<double>: " << sizeof(std::vector<double>)
              << "\n";
    std::cout << "Size of std::vector<std::string>: "
              << sizeof(std::vector<std::string>) << "\n\n";

    std::cout << "Alignment of std::vector<char>: "
              << std::alignment_of_v<std::vector<char>> << "\n";
    std::cout << "Alignment of std::vector<int>: "
              << std::alignment_of_v<std::vector<int>> << "\n";
    std::cout << "Alignment of std::vector<float>: "
              << std::alignment_of_v<std::vector<float>> << "\n";
    std::cout << "Alignment of std::vector<double>: "
              << std::alignment_of_v<std::vector<double>> << "\n";
    std::cout << "Alignment of std::vector<std::string>: "
              << std::alignment_of_v<std::vector<std::string>> << "\n\n";

    std::cout << "Size of Coordinate: " << sizeof(Coordinate) << "\n\n";
    std::cout << "Alignment of Coordinate: "
              << std::alignment_of_v<Coordinate> << "\n\n";

    std::cout << "Size of IntWrapper: " << sizeof(IntWrapper) << "\n";
    std::cout << "Size of Weather: " << sizeof(Weather) << "\n";
    std::cout << "Offset of main: " << offsetof(Weather, main) << "\n";
    std::cout << "Offset of description: " << offsetof(Weather, description)
              << "\n";
    std::cout << "Offset of icon: " << offsetof(Weather, icon) << "\n";
    std::cout << "Offset of id: " << offsetof(Weather, id) << "\n\n";

    std::cout << "Size of Main: " << sizeof(Main) << "\n";
    std::cout << "Size of WeatherData: " << sizeof(WeatherData) << "\n";
    std::cout << "Size of WeatherError: " << sizeof(WeatherError) << "\n";
}