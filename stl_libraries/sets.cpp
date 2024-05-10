#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

int main(){

    std::vector<int> v1{1,3,4,1,25,7,3,6};
    std::vector<int> v2{23,2,3,1,125,7,3,6, 5, 6};

    v1.pop_back();

    std::set<int> s1 {v1.begin(), v1.end()};
    std::set<int> s2 {v2.begin(), v2.end()};

    std::vector<int> v{};
    // std::vector<int>::iterator it,st;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(v));
    // std::set_intersection()
    std::cout << v.size() << '\n';
    for(auto st = v.begin(); st != v.end(); st++){
        std::cout << *st <<'\t';
    }
    return 0;
}