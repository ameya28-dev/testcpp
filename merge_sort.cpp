#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

struct Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration;

    Timer() { start = std::chrono::high_resolution_clock::now(); }

    void stop() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
    }

    double elapsed() {
        return duration.count() * 1000;
    }
};

class Person {
   public:
    Person() = delete;
    Person(const char* name_, int age_) : name(name_), age(age_) {};

    const std::string& get_name() const { return name; }
    const int get_age() const { return age; }

   private:
    std::string name;
    int age;
};

std::ostream& operator<<(std::ostream& stream, const std::vector<int>& vec) {
    for (const int v : vec) {
        stream << v << '\t';
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<Person>& vec) {
    for (auto& v : vec) {
        stream << "Person{name: " << v.get_name() << ", age: " << v.get_age() << "}" << '\n';
    }

    return stream;
}

void print_array(int* arr, int len) {
    std::cout << "{";
    for (int i = 0; i < len; i++) {
        std::cout << arr[i];
        if (i != len - 1) std::cout << ", ";
    }
    std::cout << "}\n";
}

void merge(int* arr, int start, int mid, int end) {
    int left_length = mid - start + 1, right_length = end - mid;
    int left[left_length];
    int right[right_length];

    for (int i = 0; i < (left_length); i++) {
        left[i] = arr[start + i];
    }
    for (int i = 0; i < (right_length); i++) {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = start;

    while (i < left_length && j < right_length) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_length) {
        arr[k] = left[i];
        i++, k++;
    }

    while (j < right_length) {
        arr[k] = right[j];
        j++, k++;
    }
}

void merge_sort(int* arr, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void merge(const std::vector<int>::iterator begin, const std::vector<int>::iterator mid, const std::vector<int>::iterator end) {
    auto left_length = std::distance(begin, mid);
    auto right_length = std::distance(mid, end);
    std::vector<int> left(left_length);
    std::vector<int> right(right_length);

    std::copy_n(begin, left_length, left.begin());
    std::copy_n(mid, right_length, right.begin());

    auto i = left.begin(), j = right.begin(), k = begin;

    while (i < left.end() && j < right.end()) {
        if (*i < *j) {
            *k = *i;
            i++;
        } else {
            *k = *j;
            j++;
        }
        k++;
    }

    if (i != left.end()) {
        std::copy(i, left.end(), k);
    }
    if (j != right.end()) {
        std::copy(j, right.end(), k);
    }
}

void merge_sort(const std::vector<int>::iterator begin, const std::vector<int>::iterator end) {
    if (std::distance(begin, end) > 1) {
        auto mid = begin + (std::distance(begin, end) / 2);

        merge_sort(begin, mid);
        merge_sort(mid, end);

        merge(begin, mid, end);
    }
}

std::vector<int> generate_vector() {
    std::vector<int> v(1000);
    std::generate(v.begin(), v.end(), [n = 1000]() mutable { return n--; });
    return v;
}

double benchmark_stl_sort() {
    auto v = generate_vector();
    Timer timer;
    std::sort(v.begin(), v.end());
    timer.stop();
    return timer.elapsed();
}

double benchmark_merge_sort() {
    auto v = generate_vector();
    Timer timer;
    merge_sort(v.begin(), v.end());
    timer.stop();
    return timer.elapsed();
}

void benchmark_sorts() {
    double ms = benchmark_merge_sort();

    double ss = benchmark_stl_sort();

    std::cout << "STL sort is faster than merge_sort by: " << ms / ss << std::endl;
}

int main() {
    int arr[] = {9, 14, 4, 6, 5, 8, 7};
    int length = sizeof(arr) / sizeof(int);
    print_array(arr, length);

    merge_sort(arr, 0, length - 1);

    print_array(arr, length);

    std::vector<int> v{10, 6, 7, 5, 2, 1, 9, 4};
    std::cout << v << std::endl;
    merge_sort(v.begin(), v.end());
    std::cout << v << std::endl;

    benchmark_sorts();

    {
        std::vector<Person> persons{Person("Ameya", 25), Person("Shreeya", 19), Person("Vignesh", 27)};

        persons.emplace_back("Anish", 23);
        persons.emplace_back("Aditi", 25);
        persons.emplace_back("Ashwin", 18);

        /// Sort by age
        std::sort(persons.begin(), persons.end(), [](Person& a, Person& b) -> bool { return a.get_age() < b.get_age(); });

        /// Sort by alphabetical order
        std::sort(persons.begin(), persons.end(), [](Person& a, Person& b) { return a.get_name() < b.get_name(); });

        /// Sort by age and then alphabetical order
        std::sort(persons.begin(), persons.end(), [](Person& a, Person& b) {
            if (a.get_age() != b.get_age()) return a.get_age() < b.get_age();
            return a.get_name() < b.get_name();
        });

        std::cout << persons << std::endl;
    }

    return 0;
}