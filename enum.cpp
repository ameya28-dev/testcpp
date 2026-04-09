#include <algorithm>
#include <array>
#include <iostream>

#define API_ERROR_LIST(X)                                         \
    X(OK, = 200, "Request Successful")                            \
    X(Created, , "Resource Created")                              \
    X(NoContent, = 204, "Success, No Content Returned")           \
    X(BadRequest, = 400, "Invalid Request Parameters")            \
    X(Unauthorized, , "Authentication Required")                  \
    X(Forbidden, = 403, "Access Denied")                          \
    X(NotFound, , "Resource Not Found")                           \
    X(ExpectationFailed, = 417, "Expectation Failed")             \
    X(ServerError, = 500, "Internal Server Error")                \
    X(NetworkTransportError, = 1000, "Network Connection Failed") \
    X(Timeout, , "Request Timed Out")                             \
    X(InvalidJson, , "Failed To Parse JSON")                      \
    X(MappingError, , "Object Mapping Failed")                    \
    X(MaxRetriesReached, , "Maximum Retry Attempts Exceeded")     \
    X(Unknown, = 2000, "An Unhandled Error Occured")

enum class ApiError {
#define AS_ENUM(name, val, desc) name val,
    API_ERROR_LIST(AS_ENUM)
#undef AS_ENUM
};

const char* toString(ApiError e) {
    switch (e) {
#define AS_CASE_NAME(name, val, desc) \
    case ApiError::name:              \
        return #name;
        API_ERROR_LIST(AS_CASE_NAME)
#undef AS_CASE_NAME
    default:
        return "Unknown";
    }
}

const char* getDescription(ApiError e) {
    switch (e) {
#define AS_CASE_DESC(name, val, desc) \
    case ApiError::name:              \
        return desc;
        API_ERROR_LIST(AS_CASE_DESC)
#undef AS_CASE_DESC
    default:
        return "Unknown";
    }
}

constexpr ApiError allApiErrors[] = {
#define AS_VALUE(name, val, desc) ApiError::name,
    API_ERROR_LIST(AS_VALUE)
#undef AS_VALUE
};

constexpr size_t apiErrorCount = sizeof(allApiErrors) / sizeof(allApiErrors[0]);

static constexpr std::array<ApiError, apiErrorCount> apiErrorList = {{
#define AS_VALUE(name, val, desc) ApiError::name,
    API_ERROR_LIST(AS_VALUE)
#undef AS_VALUE
}};

enum colors_t { black = -10, blue, green, cyan, red, yellow, orange, violet, white };

enum class Color { black, blue, green, cyan, red, yellow, orange, violet, white };
enum class Color2 { black, blue, green, cyan, red, yellow, orange };
enum class People { Good, Bad };

enum Gender { Male, Female };

enum Colors { Red, Blue };

int main() {
    colors_t mycolor;

    mycolor = green;
    if (mycolor == red) {
        mycolor = yellow;
        std::cout << mycolor << '\n';
    } else {
        std::cout << mycolor << '\n';
    }

    for (int i = black; i <= white; i++) {
        std::cout << i << '\t';
        colors_t c = static_cast<colors_t>(i);
    }

    Gender gender = Male;
    Colors colors = Red;

    if (gender == colors) {
        std::cout << '\n' << "Equal" << '\n';
    }

    Color color;
    color = Color::green;
    if (color == Color::black) {
        color = Color::green;
    }

    int green = 10;

    Color x  = Color::green;
    Color2 y = Color2::green;

    std::cout << "Size of ApiError enum: " << sizeof(ApiError) << '\n';
    std::cout << "Size of ApiError::OK enum: " << sizeof(ApiError::OK) << '\n';
    std::cout << static_cast<int>(ApiError::OK) << '\n';
    std::cout << static_cast<int>(ApiError::Created) << '\n';
    std::cout << static_cast<int>(ApiError::NoContent) << '\n';
    std::cout << static_cast<int>(ApiError::BadRequest) << '\n';
    std::cout << static_cast<int>(ApiError::Unauthorized) << '\n';
    std::cout << static_cast<int>(ApiError::Forbidden) << '\n';
    std::cout << static_cast<int>(ApiError::NotFound) << '\n';
    std::cout << static_cast<int>(ApiError::ExpectationFailed) << '\n';
    std::cout << static_cast<int>(ApiError::ServerError) << '\n';
    std::cout << static_cast<int>(ApiError::NetworkTransportError) << '\n';
    std::cout << static_cast<int>(ApiError::Timeout) << '\n';
    std::cout << static_cast<int>(ApiError::InvalidJson) << '\n';
    std::cout << static_cast<int>(ApiError::MappingError) << '\n';
    std::cout << static_cast<int>(ApiError::MaxRetriesReached) << '\n';
    std::cout << static_cast<int>(ApiError::Unknown) << '\n';

    std::cout << "Is 200 == OK?\t" << std::boolalpha << (static_cast<ApiError>(200) == ApiError::OK) << '\n';
    std::cout << "Is 417 == ExpectationFailed?\t" << (static_cast<ApiError>(417) == ApiError::ExpectationFailed)
              << '\n';
    std::cout << "Is 500 == ServerError?\t" << (static_cast<ApiError>(500) == ApiError::ServerError) << '\n';
    std::cout << "What is 406?\t";
    try {
        auto value = static_cast<ApiError>(406);
        if (value == ApiError::MappingError) {
            std::cout << "It is MappingError\n";
        } else if (value == ApiError::MaxRetriesReached) {
            std::cout << "It is MaxRetriesReached\n";
        } else {
            std::cerr << "Casting failed miserably\n";
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    for (auto error : apiErrorList) {
        std::cout << "Code: " << static_cast<int>(error) << ", name: " << toString(error)
                  << ", description: " << getDescription(error) << '\n';
    }


    return 0;
}
