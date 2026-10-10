#include <iostream>
#include <optional>

class LargeObject {
public:
    LargeObject() {
        for (int i = 0; i < 200; i++) {
            _buffer[i] = 0;
        }
    }

    ~LargeObject() = default;

    LargeObject(const LargeObject&) {
        std::cout << "Copied\n";
    }

    LargeObject(LargeObject&&) {
        std::cout << "Movied\n";
    }

    char& operator[](int i) {
        return _buffer[i];
    }

    const char operator[](int i) const {
        return _buffer[i];
    }

private:
    char _buffer[200];
};

std::optional<LargeObject> makeOptional(bool isSuccess) {
    std::cout << "makeOptional method\n";
    if (!isSuccess) {
        return {};
    }
    LargeObject obj;
    obj[0] = 0;
    return obj;
}

std::optional<LargeObject> makeOptionalBetter(bool isSuccess) {
    std::cout << "makeOptionalBetter method\n";
    std::optional<LargeObject> result;
    if (!isSuccess) {
        return result;
    }

    result.emplace();
    result.value()[0] = 0;
    return result;
}

std::optional<int> divide(double a, double b) {
    if (b == 0) {
        return {};
    }
    return a / b;
}

int main() {
    int a = 10, b = 0;
    auto result = divide(a, b);
    if (result) {
        std::cout << a << '/' << b << '=' << *result << '\n';
    } else {
        std::cout << "trying to divide by 0\n";
    }

    makeOptional(false);
    makeOptional(true);

    makeOptionalBetter(false);
    makeOptionalBetter(true);
}
