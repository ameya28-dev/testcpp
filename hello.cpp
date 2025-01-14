#include <vector>
#include <math.h>
#include <iostream>
#include <functional>


struct vertex {
  double x, y, z;

  double magnitude() { return sqrt(x * x + y * y + z * z); }

  bool operator==(const vertex &other) {
    return this->x = other.x && this->y == other.y && this->z == other.z;
  }
};

std::vector<int>::const_iterator find_mismatch(const std::vector<int> &v,
                                               const std::vector<int> &v2) {
  if (v.size() != v2.size()) {
    std::cout << "v and v2 are different size => mismatch found\n";
    return v2.end();
  }
  if (std::pair<std::vector<int>::const_iterator,
                std::vector<int>::const_iterator>
          res = std::mismatch(v.cbegin(), v.cend(), v2.cbegin());
      res.first == v.cend() && res.second == v2.cend()) {
    std::cout << "v and v2 have no mismatch\n";
    return v2.end();
  } else {
    auto [first, second] = res;
    std::cout << "v and v2 has a mismatch\n"
              << "First position:\t" << std::distance(v.cbegin(), first)
              << "Value:\t" << *first << "\n"
              << "Second position:\t" << std::distance(v2.cbegin(), second)
              << "Value:\t" << *second << "\n";
    return second;
  }
}

std::function<bool(int)> is_positive = [](const int a) { return a % 2 == 0; };

std::function<bool(int)> is_prime = [](int a) {
  if (a == 2 || a == 3)
    return true;

  if (a % 2 == 0)
    return false;

  int p = 2;

  while (p * p <= a) {
    if (a % p == 0)
      return false;
    p++;
  }

  return true;
};

// std::function<int()> gen_fib = [m = 1, n = 1]() mutable {
//   int next = m;
//   m = n;
//   n = +next;
//   return next;
// };

// template <size_t s>
// std::ostream &operator<<(std::ostream &instream, const std::array<int, s>
// arr) {
//   // for(const int i:arr) {
//   //   instream << i << '\t';
//   //}

//   std::for_each(arr.begin(), arr.end(),
//                 [&instream](int i) { instream << i << '\t'; });

//   return instream;
// }

int main() {
  std::cout << "Hello World!" << std::endl;
  std::vector<int> v{3, 5, 9, 7, 4};
  std::vector<int> v2{3, 5, 9, 8, 4};

  if (std::vector<int>::const_iterator res =
          std::find_if(v.cbegin(), v.cend(), is_positive);
      res != v.cend()) {
    std::cout << *res << std::endl;
  } else {
    std::cout << "Not found" << std::endl;
  }

  std::cout << "Before changing v2\n";
  std::vector<int>::const_iterator it = find_mismatch(v, v2);

  std::cout << "After changing v2\n";

  int position = std::distance(v2.cbegin(), it);

  v2[position] = v[position];

  find_mismatch(v, v2);

  std::cout << std::count(v.begin(), v.end(), 5) << '\n';
  std::cout << std::count_if(v.begin(), v.end(), is_prime) << std::endl;
  {
    std::string s1 = "Hello world! I am Ameya G Mahale";
    std::string s2;
    std::copy_if(s1.cbegin(), s1.cend(), std::back_inserter(s2),
                 [](const char a) { return (a > 64 && a < 91); });
    std::cout << s2 << '\n';
    std::copy_n(s1.cbegin(), 8, std::back_inserter(s2));
    std::cout << s2 << '\n';

    std::array<int, 5> arr1{1, 2, 3, 4, 5};
    std::array<int, 5> arr2;
    std::copy(arr1.begin(), arr1.end(), arr2);
    // for (int a : arr2)
    //   std::cout << a << '\t';
  }
//   {
//     std::array<int, 5> arr{1, 2, 3, 4, 5};
//     for (int i : arr) {
//       std::cout << i << '\n';
//     }
//   }
  return 0;
}
