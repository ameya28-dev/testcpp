#include <iostream>
#include <vector>
#include <algorithm>

bool comparator(std::pair<int, int> p1, std::pair<int,int> p2){
    return p1.second < p2.second;
}

int main(){
    std::vector<int> g1;

    for(int i = 1; i<= 5; i++){
        g1.push_back(i);
    }
    
    // Traversing  using indices
    for(int i = 0; i < g1.size(); i++){
        std::cout << g1[i] << '\t';
        (g1[i])++;
    }
    std::cout << '\n';

    // Traversing using iterator
    std::vector<int>::iterator ptr;
    for(ptr = g1.begin(); ptr != g1.end(); ptr++){
        std::cout << *ptr << '\t';
        (*ptr)++;
    }
    std::cout << '\n';

    // Traversing using auto
    for(auto x:g1){
        std::cout << x << '\t';
        x++; 
    }
    std::cout << '\n';

    g1.pop_back();
    for(auto x:g1){
        std::cout << x << '\t';
    }
    std::cout << '\n';

    g1.back() += 100;
    // for(auto i = g1.cbegin(); i != g1.cend(); i++){
    //     (*i)++;
    // }

    std::vector<int> g2(3,80);
    for(auto ptr = g2.begin();ptr != g2.end(); ptr++){
        std::cout << *ptr << '\t';
    }
    std::cout << '\n';

    std::cout << "Swapping vectors using std::swap" << '\n';
    std::cout << "Addresses of vectors, g1:" << &g1 <<"\t g2:" << &g2 << '\n';
    swap(g1, g2);
    std::cout << "Addresses of vectors, g1:" << &g1 <<"\t g2:" << &g2 << '\n';
    std::cout << "g1:\t";
    for(auto x: g1){
        std::cout << x <<'\t';
    } 
    std::cout << '\n';

    std::cout << "g2:\t";
    for(auto x: g2){
        std::cout << x <<'\t';
    } 
    std::cout << '\n';

    std::cout << "Swapping vectors using std::vector::swap" << '\n';
    g1.swap(g2);
    std::cout << "Addresses of vectors, g1:" << &g1 <<"\t g2:" << &g2 << '\n';
    for(auto x: g1){
        std::cout << x <<'\t';
    } 
    std::cout << '\n';

    std::cout << "g2:\t";
    for(auto x: g2){
        std::cout << x <<'\t';
    } 
    std::cout << '\n';

    std::cout << "Sorting using std::sort" << '\n';
    g1.push_back(4);
    g1.push_back(11);
    g1.push_back(59);
    g1.push_back(0);

    for(int i = 0; i < g1.size(); i++){
        std::cout << g1[i] << '\t';
    }
    std::cout << '\n';

    std::cout << "By default, in ascending order" << '\n';
    sort(g1.begin(), g1.end());
    for(const auto x: g1){
        std::cout << x << '\t';
    }
    std::cout << '\n';

    std::cout << "For descending order" << '\n';
    sort(g1.begin(), g1.end(), std::greater<int>());
    for(std::vector<int>::iterator i = g1.begin(); i < g1.end(); i++){
        std::cout << *i << '\t';
    }
    std::cout << '\n';

    std::pair<int, char> p1; p1.first = 1; p1.second = 'f';
    std::pair<int, char> p2 = std::make_pair(2,'g');

    std::cout << "Write a program to reduce the given array" << '\n';
    std::cout << "Meaning update the smallest element to 0, next to 1 and so on for all the elements in place" << '\n';

    int arr[] = {10,16,7,14,5,3,12,9};
    std::vector<std::pair<int, int>> vec;

    for(int i = 0; i < sizeof(arr)/ sizeof(int); i++){
        vec.push_back(std::make_pair(i, arr[i]));
    }

    sort(vec.begin(), vec.end(), comparator);

    for(int i = 0; i < sizeof(arr)/ sizeof(int); i++){
        arr[vec[i].first] = i;
    }

    std::cout << '\n' << "Reducing array: " << '\n';
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
        std::cout << arr[i] << "\t";
    }

    std::cin.get();

    return 0;
}