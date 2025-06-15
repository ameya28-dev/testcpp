#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

class Stream {
   public:
    using flags_type = int;

   public:
    flags_type flags() const { return flags_; }

    flags_type flags(flags_type newf) { return std::exchange(flags_, newf); }

   private:
    flags_type flags_ = 0;
};

void f() { std::cout << "f()"; }

int main() {
    Stream s;

    std::cout << s.flags() << '\n';
    std::cout << s.flags(12) << '\n';
    std::cout << s.flags() << '\n';

    std::vector<int> v;

    std::exchange(v, {1, 2, 3, 4});

    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n\n";

    void (*fun)();

    std::exchange(fun, f);
    fun();

    std::cout << "\n\nFibonacci sequence:\t";

    for (int a{0}, b{1}; a < 100; a = std::exchange(b, a + b)) {
        std::cout << a << ", ";
    }
}
