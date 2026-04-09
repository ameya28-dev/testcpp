#include <iostream>
#include <memory>
#include <string>
#include <utility>

class constructors {
   private:
    std::string data;

   public:
    constructors() {
        std::cout << "default constructor called\n";
        data = "";
    }

    constructors(const std::string& s) {
        std::cout << "copy constructor called\n";
        data = s;
    }

    constructors(std::string&& s) {
        std::cout << "move constructor called\n";
        data = s;
    }

    ~constructors() = default;
};

struct c_string_deleter {
    void operator()(char* ptr) const noexcept {
        if (ptr != nullptr) {
            free(ptr);
        }
    }
};

char* create_string() {
    char* str = (char*)malloc(6 * sizeof(char));
    str[0] = 'h';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';
    return str;
}

int main() {
    std::string s = "Hello";
    constructors c1{s};
    constructors c2{"world"};

    using c_string = std::unique_ptr<char, c_string_deleter>;
    
    auto str = c_string(create_string());

    std::cout << str.get() << '\n';
}
