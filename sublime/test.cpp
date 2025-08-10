#include <iomanip>
#include <iostream>
#include <string>
#include <exception>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <functional>
#include <unordered_map>
#include <optional>
#include <utility>
#include <numeric>
#include <algorithm>

struct complex {
	double real, imag;

	const double magnitude() const {
		return sqrt(real * real + imag * imag);
	}

	bool is_zero() const {
		return real == 0 && imag == 0;
	}

	complex operator+(const complex& c) const {
		return {real + c.real, imag + c.imag};
	}

	complex operator-(const complex& c) const {
		return {real - c.real, imag - c.imag};
	}

	complex operator*(const complex& c) const {
		return {real * c.real - imag * c.imag, real * c.imag  + imag * c.real};
	}

	complex inv() const {
		return complex{real, imag * -1} / magnitude();
	}

	complex operator/(const complex& c) const {
		if (c.is_zero()) {
			throw std::invalid_argument("Cannot divide by zero");
		}

		if (is_zero()) {
			return *this;
		}

		return *this * c.inv();

	}

	complex operator/(const double d) const {
		return {real / d, imag / d};
	}

	const complex unit() const {
		return complex{real, imag} / magnitude();
	}

	friend std::ostream& operator<<(std::ostream& stream, const complex& c) {
		stream << "(" << c.real << " " << (c.imag > 0 ? "+ " : "- ") << std::abs(c.imag) << "i)";
		return stream;
	}
};

std::ostream& operator<<(std::ostream& stream, const std::vector<int>& v) {
	if (v.empty()) {
		return stream << "std::vector<int>{}";
	}

	stream << "std::vector<int>{" << *(v.begin());
	std::for_each(std::next(v.begin()), v.end(), [&stream](const int a) {stream << "," << a;});
	return stream << "}";
}

std::ostream& operator<<(std::ostream& stream, const std::set<int>& s) {
	if (s.empty()) {
		return stream << "std::set<int>{}";
	}

	stream << "std::set<int>{" << *s.begin();
	std::for_each(std::next(s.begin()), s.end(), [&stream](const int x) {stream << "," << x;});
	return stream << "}";
}

std::ostream& operator<<(std::ostream& stream, const std::unordered_map<int, std::string>& map) {
	if (map.empty()) {
		return stream << "std::unordered_map<int, std::string>{}";
	}

	stream << "std::unordered_map<int, std::string>{{" << map.begin()->first << "," << std::quoted(map.begin()->second) << "}" ;
	std::for_each(std::next(map.begin()), map.end(), [&stream](const std::pair<int, std::string>& pair) {stream << ",{" << pair.first << "," << std::quoted(pair.second) << "}";});
	return stream << "}";
}

std::ostream& operator<<(std::ostream& stream, const std::unordered_map<int, int>& map) {
	if (map.empty()) {
		return stream << "std::unordered_map<int, int>{}";
	}

	stream << "std::unordered_map<int, int>{{" << map.begin()->first << "," << map.begin()->second << "}" ;
	std::for_each(std::next(map.begin()), map.end(), [&stream](const std::pair<int, int>& pair) {stream << ",{" << pair.first << "," << pair.second << "}";});
	return stream << "}";
}

void find_intersection(std::vector<int> v1, std::vector<int> v2, std::vector<int>& output) {
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(output));
}



class CodeMap
{
public:

	static const std::optional<std::string> name_if(int code) {
		const std::unordered_map<int, std::string>::iterator& res = map.find(code);
		if (res != map.end()) {
			return res->second;
		}
		else {
			return {};
		};
	}

	static const std::string& name(int code)  {
		return map.at(code);
	}

	static bool insert_if(const std::pair<int, const std::string>& pair) {
		if (map.find(pair.first) != map.end()) {
			return false;
		}
		map[pair.first] = pair.second;
		return true;
	}

	static bool update_if(const std::pair<int, const std::string>& pair) {
		if (map.find(pair.first) == map.end()) {
			return false;
		}
		map[pair.first] = pair.second;
		return true;
	}

	static bool delete_if(int code) {
		if (map.find(code) == map.end()) {
			return false;
		}
		map.erase(code);
		return true;
	}

	static bool contains(int code) {
		return map.find(code) != map.end();
	}

	static void print() {std::cout << map << std::endl;}

private:
	static std::unordered_map<int, std::string> map;

};

std::unordered_map<int, std::string> CodeMap::map  = {{1, "Hubli"}, {2, "Dharwad"}, {3, "Mumbai"}};

std::unordered_map<int, int> two_sum(const std::vector<int>& v, int sum) {
	std::unordered_map<int, int> res{};
	std::unordered_map<int, int> map{};
	for (int i = 0; i < v.size(); i++) {
		if (map.find(sum - v[i]) == map.end()) {
			map[v[i]] = i;
		} else {
			res[i] = map[sum - v[i]];
		}
	}
	return res;
}


struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* add_two_numbers(ListNode* l1, ListNode* l2) {
	ListNode* head = nullptr;
	ListNode* temp = head;
	int carry = 0;

	while (l1 != nullptr || l2 != nullptr || carry != 0) {
		int first = l1 != nullptr ? l1->val : 0;
		int second = l2 != nullptr ? l2->val : 0;

		int sum  = first + second + carry;
		carry = sum / 10;
		ListNode* ptr = new ListNode(sum % 10);
		if (head == nullptr) {
			head = ptr;
			temp = head;
		} else {
			temp->next = ptr;
			temp = temp->next;
		}

		l1 = l1 != nullptr ? l1->next : nullptr;
		l2 = l2 != nullptr ? l2->next : nullptr;
	}

	return head;
}

int main()
{
	const complex c1 {1, 2};
	const complex c2 {3, 4};

	complex cm = c1 * c2;

	std::cout << c1 + c2 << std::endl;
	std::cout << c1 - c2 << std::endl;
	std::cout << cm << std::endl;
	std::cout << cm / 5 << std::endl;
	std::cout << complex{0, 5} .unit() << std::endl;
	std::cout << c1 / c2 << std::endl;
	std::cout << c2.inv() << std::endl;

	try
	{
		cm / complex{0, 0};
	}
	catch (const std::invalid_argument& ex) {
		std::cerr << ex.what() << std::endl;
	}

	std::vector<int> v1{2, 34, 6, 7, 8, 9, 97, 6, 5, 5};

	v1.erase(std::remove_if(v1.begin(), v1.end(), [](int a) {return a == 5;}), v1.end());

	std::cout << v1 << std::endl;

	std::vector<int> v2{5, 7, 8, 2};
	std::vector<int> intersect;

	find_intersection(v1, v2, intersect);
	std::cout << intersect << std::endl;

	std::set<int> s;
	std::transform(intersect.begin(), intersect.end(), std::inserter(s, std::begin(s)), [](int a) {return a * a + 2;});

	std::cout << s << std::endl;


	std::function<bool(int)> is_even = [](const int x) {return x % 2 != 0;};
	std::vector<int> vec(std::count_if(v1.cbegin(), v1.cend(), is_even));
	std::copy_if(v1.cbegin(), v1.cend(), vec.begin(), is_even);
	vec.push_back(11);
	std::cout << vec << std::endl;

	std::cout << CodeMap::name(1) << std::endl;
	std::cout << CodeMap::name_if(4).value_or("Not found") << std::endl;

	CodeMap::print();

	CodeMap::insert_if({1, "Bangalore"});
	CodeMap::insert_if({4, "Bangalore"});

	CodeMap::print();

	CodeMap::update_if({5, "Bangalore"});
	CodeMap::update_if({1, "Chennai"});

	CodeMap::print();

	CodeMap::delete_if(1);
	CodeMap::delete_if(0);

	CodeMap::print();

	std::sort(v1.begin(), v1.end());
	std::cout << v1 << std::endl;

	std::vector<int> nums {3, 3, 2, 5, 6, 4, 3};
	std::cout << two_sum(nums, 6) << std::endl;

	std::vector<int> gen(5);
	std::iota(gen.begin(), gen.end(), 1);
	std::cout << gen << std::endl;

	std::generate(gen.begin(), gen.end(), [n = 1]() mutable {return pow(n++, 2);});
	std::cout << gen << std::endl;

	std::vector<int> filtered {};
	std::copy_if(gen.begin(), gen.end(), std::back_inserter(filtered), [](int x) {return CodeMap::contains(x);});
	std::cout << filtered << std::endl;

	return 0;
}