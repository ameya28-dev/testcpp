#include <iostream>
#include <vector>
#include <algorithm>
using std::cout, std::vector, std::pair;

bool comparator(pair<int, int> p1, pair<int,int> p2){
    return p1.second < p2.second;
}

int main(){
    vector<int> g1;

    for(int i = 1; i<= 5; i++){
        g1.push_back(i);
    }
    
    // Traversing  using indices
    for(int i = 0; i < g1.size(); i++){
        cout << g1[i] << '\t';
        (g1[i])++;
    }
    cout << '\n';

    // Traversing using iterator
    vector<int>::iterator ptr;
    for(ptr = g1.begin(); ptr != g1.end(); ptr++){
        cout << *ptr << '\t';
        (*ptr)++;
    }
    cout << '\n';

    // Traversing using auto
    for(auto x:g1){
        cout << x << '\t';
        x++; 
    }
    cout << '\n';

    g1.pop_back();
    for(auto x:g1){
        cout << x << '\t';
    }
    cout << '\n';

    g1.back() += 100;
    // for(auto i = g1.cbegin(); i != g1.cend(); i++){
    //     (*i)++;
    // }

    vector<int> g2(3,80);
    for(auto ptr = g2.begin();ptr != g2.end(); ptr++){
        cout << *ptr << '\t';
    }
    cout << '\n';

    cout << "Swapping vectors using std::swap" << '\n';
    cout << "Addresses of vectors, g1:" << &g1 <<"\t g2:" << &g2 << '\n';
    swap(g1, g2);
    cout << "Addresses of vectors, g1:" << &g1 <<"\t g2:" << &g2 << '\n';
    cout << "g1:\t";
    for(auto x: g1){
        cout << x <<'\t';
    } 
    cout << '\n';

    cout << "g2:\t";
    for(auto x: g2){
        cout << x <<'\t';
    } 
    cout << '\n';

    cout << "Swapping vectors using std::vector::swap" << '\n';
    g1.swap(g2);
    cout << "Addresses of vectors, g1:" << &g1 <<"\t g2:" << &g2 << '\n';
    for(auto x: g1){
        cout << x <<'\t';
    } 
    cout << '\n';

    cout << "g2:\t";
    for(auto x: g2){
        cout << x <<'\t';
    } 
    cout << '\n';

    cout << "Sorting using std::sort" << '\n';
    g1.push_back(4);
    g1.push_back(11);
    g1.push_back(59);
    g1.push_back(0);

    for(int i = 0; i < g1.size(); i++){
        cout << g1[i] << '\t';
    }
    cout << '\n';

    cout << "By default, in ascending order" << '\n';
    sort(g1.begin(), g1.end());
    for(const auto x: g1){
        cout << x << '\t';
    }
    cout << '\n';

    cout << "For descending order" << '\n';
    sort(g1.begin(), g1.end(), std::greater<int>());
    for(vector<int>::iterator i = g1.begin(); i < g1.end(); i++){
        cout << *i << '\t';
    }
    cout << '\n';

    pair<int, char> p1; p1.first = 1; p1.second = 'f';
    pair<int, char> p2 = std::make_pair(2,'g');

    cout << "Write a program to reduce the given array" << '\n';
    cout << "Meaning update the smallest element to 0, next to 1 and so on for all the elements in place" << '\n';

    int arr[] = {10,16,7,14,5,3,12,9};
    vector <pair<int, int>> vec;

    for(int i = 0; i < sizeof(arr)/ sizeof(int); i++){
        vec.push_back(std::make_pair(i, arr[i]));
    }

    sort(vec.begin(), vec.end(), comparator);

    for(int i = 0; i < sizeof(arr)/ sizeof(int); i++){
        arr[vec[i].first] = i;
    }

    cout << '\n' << "Reducing array: " << '\n';
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
        cout << arr[i] << "\t";
    }

    return 0;
}