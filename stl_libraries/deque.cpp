#include <deque>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

void slidingwindowmaximuminarray(int* arr, int n, int k){
    int *res = new int[n-k+1];
    for(int i = 0; i<n; i++){
        int max = arr[i];
        for(int j = i+1; j < i+k; j++){
            if(arr[j] > arr[j-1]) max = arr[j];
        }
        res[i] = max;
    }
    for(int i = 0; i < n-k+1; i++){
        std::cout <<res[i];
    }
    delete[] res;
}

int main(){
    std::deque<int> dq;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(3);
    dq.push_front(4);

    for(std::deque<int>::iterator itr = dq.begin(); itr != dq.end(); itr++){
        std::cout << *itr << '\t';
    }
    std::cout << '\n';

    dq.pop_back();
    dq.pop_front();
    for(const auto i:dq){
        std::cout << i << '\t';
    }
    std::cout << '\n';

    int arr[8] = {1,3,-1,-3,5,3,6,7};
    // slidingwindowmaximuminarray(arr, sizeof(arr)/sizeof(int), 3);


    return 0;
}