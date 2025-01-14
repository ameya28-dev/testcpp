#include <algorithm>
#include <chrono>
#include <cmath>
#include <forward_list>
#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <thread>
#include <unordered_map>
#include <variant>
#include <vector>

#define WAIT std::cin.get()
#define LOG(x) std::cout << x << std::endl

const std::string &more_frequent(const std::unordered_map<std::string, int> &word_counts, const std::string &word1, const std::string &word2) {
    if (word_counts.find(word1) == word_counts.end()) return "";
    if (word_counts.find(word2) == word_counts.end()) return "";
    return word_counts.at(word1) > word_counts.at(word2) ? word1 : word2;
}

void increment(int *value) {
    (*value)++;
}

void increment_ref(int &value) {
    value++;
}

struct Structure {
    int x, y;

    Structure() {
        x = 1;
        y = 1;
    }

    Structure(int x, int y) : x(x), y(y) {}
} ex_struct;

struct Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration;

    Timer();
    ~Timer();
};

Timer::Timer() {
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "Timer took " << duration.count() * 1000.0 << "ms" << std::endl;
}

template <typename T, int N>
class Array {
   private:
    T m_array[N]{0};

   public:
    int get_size() { return N; }
};

template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}

void function_pointer() {
    std::cout << "Function Pointer" << std::endl;
}

void PrintIfOdd(int x) {
    if (x % 2) std::cout << x << std::endl;
}

void func(int *__restrict ptr) {
}

void ForEach(std::vector<int> &vector, void (*func)(int)) {
    for (int x : vector) {
        func(x);
    }
}

void ForEach2(std::vector<int> &vector, std::function<void(int)> func) {
    for (int x : vector) {
        func(x);
    }
}

void see_time() {
    Timer timer;
    for (int i = 0; i < 5; i++) std::cout << i << "\n";
}

struct Entity {
    int x, y;
};

struct Vertex {
    int x, y, z;

    Vertex(int x, int y, int z) : x(x), y(y), z(z) {}
    double magnitude() {
        return sqrt(x * x + y * y + z * z);
    }

    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    bool operator==(const Vertex &other) {
        return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
    }
};

bool operator==(const Vertex &left, const Vertex &right) {
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

std::ostream &operator<<(std::ostream &stream, const Vertex &vertex) {
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::vector<int> &vec) {
    for (const int v : vec) {
        stream << v << '\t';
    }

    return stream;
}

template <size_t S>
std::ostream &operator<<(std::ostream &stream, const std::array<int, S> &arr) {
    // for (const int v : arr) {
    //     stream << v << '\t';
    // }

    std::for_each(arr.begin(), arr.end(), [&stream](int i) { stream << i << '\t'; });

    return stream;
}

class String {
   private:
    char *m_Buffer;
    unsigned int m_size;
};

int main() {
    {
        int a = 4;
        increment(&a);
        increment_ref(a);
        std::cout << a << std::endl;

        std::vector<int> vec{1, 2, 3, 4, 5};

        print(ex_struct.x);
        print(ex_struct.y);
        print("Hello");

        Structure init{1, 2};
        print(init.x);
        print(init.y);

        LOG("Hello World!");

        void (*function)() = function_pointer;
        function();

        int multiplier = 2;

        double s = static_cast<double>(multiplier);
        ForEach(vec, PrintIfOdd);
        ForEach(vec, [](int x) {if (!(x % 2)) std::cout << x << std::endl; });  // lambda
        ForEach2(vec, [&multiplier](int x) { std::cout << x * multiplier << std::endl; });

        std::vector<int>::iterator it = std::find_if(vec.begin(), vec.end(), [](int value) { return value > 3; });
        print(*it);

        see_time();

        const std::size_t z = 6;
        std::array<int, z> values{3, 1, 5, 4, 6, 7};
        std::sort(values.begin(), values.end(), [](int a, int b) {if(a<2) return false; if(b>6) return true; return true; });
        for (int value : values) std::cout << value << "\t";
        std::cout << '\n';

        int a1 = 50;
        double b = *(double *)&a1;
        std::cout << b << '\n';

        Entity e{5, 8};
        int *position = (int *)&e;
        int y = *(int *)((char *)&e + 4);
        std::cout << position[0] << ", " << position[1] << '\n';
        std::cout << sizeof(int) << '\n';
        std::cout << y << '\n';

        std::variant<std::string, int> data;
        data = 'a';
        if (const int *pval = std::get_if<int>(&data)) {
            std::cout << "variant value: " << *pval << '\n';
        } else {
            std::cout << "failed to get value!" << '\n';
        }
    }

    {
        std::array<int, 10> arr{1, 4, 5, 6, 10, 2, 6, 5, 6, 6};
        std::function<bool(int)> is_positive = [](int a) { return a % 2 == 0; };
        if (std::array<int, 10>::const_iterator it = std::find_if(arr.cbegin(), arr.cend(), is_positive); it != arr.cend()) {
            std::cout << *it << std::endl;
        } else {
            std::cout << "Not found" << std::endl;
        }
        std::array<int, 3> seq{5, 6, 10};

        auto result = std::search(arr.begin(), arr.end(), seq.begin(), seq.end());
        if (result != arr.end()) std::cout << *result << std::endl;
        if (auto result = std::adjacent_find(arr.begin(), arr.end()); result != arr.end()) std::cout << "Adjacent found\t" << *result << std::endl;
    }

    {
        std::vector<Vertex> vec;
        vec.emplace_back(1, 2, 3);
        vec.emplace_back(4, 5, 6);
        vec.emplace_back(4, 5, 3);
        vec.emplace_back(4, 3, 5);
        vec.emplace_back(1, 5, 6);
        vec.emplace_back(10, 5, 6);
        vec.emplace_back(4, 1, 6);
        std::sort(vec.begin(), vec.end(), [](Vertex a, Vertex b) { return a.magnitude() < b.magnitude(); });
        for (Vertex v : vec) std::cout << v << std::endl;

        if (auto res = std::adjacent_find(vec.begin(), vec.end(), [](Vertex a, Vertex b) { return a.magnitude() == b.magnitude(); });
            res != vec.end()) {
            std::cout << "Adjacent vertices:\n1.\t" << *res << "\n2.\t" << *(++res) << std::endl;
            std::cout << "Found at:\t" << std::distance(vec.begin(), res) << '\n';
        }
    }

    {
        std::vector<int> v1{2, 3, 4, 5};
        std::vector<int> v2{1, 2, 3, 4, 5};
        std::vector<Vertex> vec1;
        vec1.emplace_back(1, 2, 3);
        vec1.emplace_back(4, 5, 6);
        vec1.emplace_back(4, 5, 3);
        vec1.emplace_back(4, 3, 5);
        vec1.emplace_back(1, 5, 6);
        vec1.emplace_back(10, 5, 6);
        vec1.emplace_back(4, 1, 6);
        std::vector<Vertex> vec2;
        vec2.emplace_back(1, 2, 3);
        vec2.emplace_back(4, 5, 6);
        vec2.emplace_back(4, 3, 5);
        vec2.emplace_back(4, 5, 3);
        vec2.emplace_back(1, 5, 6);
        vec2.emplace_back(10, 5, 6);
        vec2.emplace_back(4, 1, 6);

        {
            if (v1.size() == v2.size()) {
                std::pair<std::vector<int>::iterator, std::vector<int>::iterator> res = std::mismatch(v1.begin(), v1.end(), v2.begin());
                if (auto [x, y] = res; x == v1.end() && y == v2.end()) {
                    std::cout << "No mismatches found\n";
                } else {
                    std::cout << "Mismatch found: \t" << *x << '\t' << *y << '\n';
                }
            } else {
                std::cout << "Containers of different size => Mismatch found\n";
            }

            std::function<bool(const Vertex &, const Vertex &)> is_magnitude_same = [](const Vertex &a, const Vertex &b) { return a.magnitude() == b.magnitude(); };
            std::pair<std::vector<Vertex>::const_iterator, std::vector<Vertex>::const_iterator> result = std::mismatch(vec1.cbegin(), vec1.cend(), vec2.cbegin(), is_magnitude_same);
            std::cout << "vec 1 and vec2 match by magitude:\t" << (result.first == vec1.cend()) << '\n';
            std::cout << "vec 1 and vec2 match by vertices:\t" << (std::mismatch(vec1.cbegin(), vec1.cend(), vec2.cbegin(), [](const Vertex &first, const Vertex &second) { return (first.x == second.x) && (first.y == second.y) && (first.z == second.z); }).first == vec1.cend()) << '\n';

            if (std::equal(v1.cbegin(), v1.cend(), ++(v2.cbegin()))) {
                std::cout << "v1 and v2 are equal\n";
            } else {
                std::cout << "v1 and v2 are not equal\n";
            }

            std::cout << "vec 1 and vec2 are equal:\t" << std::equal(vec1.cbegin(), vec1.cend(), vec2.cbegin()) << '\n';
            std::cout << "vec 1 and vec2 are equal by magitude:\t" << std::equal(vec1.cbegin(), vec1.cend(), vec2.cbegin(), is_magnitude_same) << '\n';
        }

        {
            std::cout << "All of vec1:\t" << std::all_of(vec1.cbegin(), vec1.cend(), [](const Vertex v) { return v.magnitude() <= 10; }) << "\n";
            std::cout << "Any of vec1:\t" << std::any_of(vec1.cbegin(), vec1.cend(), [](const Vertex v) { return v.magnitude() <= 10; }) << "\n";
            std::cout << "None of vec1:\t" << std::none_of(vec1.cbegin(), vec1.cend(), [](const Vertex v) { return v.magnitude() <= 10; }) << "\n";
        }

        {
            std::cout << "Count of vertex (4, 5, 3) in vec1:\t" << std::count(vec1.begin(), vec1.end(), Vertex(4, 5, 3)) << '\n';
            std::cout << "Count of vertices with same magnitude as (4, 5, 3) in vec1:\t" << std::count_if(vec1.begin(), vec1.end(), [](const Vertex c) { return c.magnitude() == Vertex(4, 5, 3).magnitude(); }) << '\n';
        }

        {
            std::vector<int> v_copy;
            v_copy.resize(v1.size());
            std::copy(v1.begin(), v1.end(), v_copy.begin());
            v_copy.resize(v_copy.size() + (v2.size()));

            std::copy(v2.begin(), v2.end(), v_copy.begin() + v1.size());
            std::cout << v_copy << std::endl;
            {
                Timer t;
                std::vector<Vertex> vec_copy;
                std::function<bool(const Vertex &)> magnitude_less_than_ten = [](const Vertex &v) { return v.magnitude() <= 10; };
                vec_copy.reserve(std::count_if(vec1.begin(), vec1.end(), magnitude_less_than_ten));
                std::copy_if(vec1.crbegin(), vec1.crend(), std::back_inserter(vec_copy), magnitude_less_than_ten);
                // for (const Vertex &v : vec_copy) std::cout << v << '\n';
            }

            {
                std::array<int, 5> arr1{1, 2, 3, 4, 5};
                std::array<int, 5> arr2;
                // arr2 = arr1;
                // auto itr = arr1.begin();
                std::copy(arr1.begin(), arr1.end(), arr2.begin());
                std::cout << "Copying array\n";
                arr1[4] = 4;
                for (int a : arr1) std::cout << a << '\t';
                std::cout << '\n';
                for (int a : arr2) std::cout << a << '\t';
            }

            {
                std::vector<int> v(10);
                std::generate(v.begin(), v.end(), [n = 0]() mutable { return pow(++n, 2); });
                std::cout << "\nGenerate vector:\t" << v << '\n';

                std::array<int, 20> arr;
                auto gen_fibonacci = [m = 1, n = 1]() mutable {
                    int next = m;
                    m = n;
                    n += next;
                    return next;
                };

                std::generate_n(arr.begin(), 10, gen_fibonacci);
                std::generate(arr.begin() + 10, arr.end(), gen_fibonacci);
                std::cout << "\nGenerate array:\t" << arr << '\n';

                std::unordered_map<int, int> map;

                std::function<std::pair<int, int>(int)> generate_pair = [](int n) { return std::make_pair(n, n * n); };
                for (int i = 1; i <= 5; i++) {
                    map.insert(generate_pair(i));
                }

                for (const auto &[key, value] : map) {
                    std::cout << "Key:\t" << key << "\tValue:" << value << "\n";
                }
            }
        }

        {
            std::array<int, 10> arr;
            std::array<int, 15> arr2{};
            std::fill_n(arr.begin(), 5, 1);
            std::generate(arr.begin() + 5, arr.end(), [n = 100]() mutable { n /=2; return n; });
            std::reverse_copy(arr.begin(), arr.end(), arr2.begin() + 5);
            std::cout << arr << '\n';
            std::cout << arr2 << '\n';

            std::forward_list<int> f_list(10);
            std::generate(f_list.begin(), f_list.end(), [n = 10]() mutable { return n--; });
            f_list.reverse();
            for (const int i : f_list) std::cout << i << '\t';
        }
    }

    {
        std::array<int, 10> arr{1, 2, 3, 4, 4, 6, 7, 8, 9, 10};
        std::remove(arr.begin(), arr.end(), 4);
        std::cout << '\n'
                  << arr << '\n';
        arr.fill(0);
        std::cout << '\n'
                  << arr << '\n';

        std::vector<Vertex> v;
        v.reserve(4);
        v.emplace_back(1, 2, 3);
        v.emplace_back(1, 2, 3);
        v.emplace_back(4, 5, 6);
        v.emplace_back(3, 4, 5);
        std::vector<Vertex>::iterator it = std::remove(v.begin(), v.end(), Vertex(1, 2, 3));

        v.erase(it, v.end());

        for (const Vertex &i : v) std::cout << i << '\n';
    }

    {
        std::vector<int> v1{1, 23, 4, 6, 5, 7, 8, 8};
        std::vector<int> v2{1, 4, 6, 5, 8, 9, 10};
        std::vector<int> res;

        std::set<int> s1(v1.begin(), v1.end());
        std::set<int> s2(v2.begin(), v2.end());

        std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(res));
        for (const int i : res) std::cout << i << '\t';
    }

    {
        std::cout << "\n\nstd::sample example\n";
        std::vector<int> ai_bots{1, 3, 7, 6, -2, 1, 5, 6, 7, 8, 13, 56, 12, 78, 90, 12};
        std::vector<int> out;
        std::sample(ai_bots.begin(), ai_bots.end(), std::back_inserter(out), 3, std::mt19937{std::random_device{}()});
        std::cout << out << '\n';

        std::array<int, 6> sample;
        std::sample(ai_bots.begin(), ai_bots.end(), sample.begin(), sample.size(), std::mt19937{std::random_device{}()});

        for (const int i : sample) std::cout << i << '\t';
    }

    {
        std::cout << "\n\nstd::rotate example\n";
        std::array<int, 10> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto it = std::rotate(arr.begin(), arr.begin() + 3, arr.end());
        std::cout << arr << '\n';
        std::cout << *it << '\n';

        std::forward_list<int> fl(10);
        std::generate_n(fl.begin(), 10, [n = 1]() mutable {
            int a = n;
            n++;
            return a * a;
        });

        for (auto i : fl) std::cout << i << '\t';
    }

    {
        std::string i = "12";
        std::cout << '\n'
                  << 20 + std::stoi(i) << '\n';

        std::vector<std::string> s{"Ameya", "is", "4", "years", "old"};
        s[2] = std::to_string(24);

        for (const std::string &x : s) std::cout << x << '\t';
    }

    return 0;
}