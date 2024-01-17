#include <iostream>
#include <chrono>
#include <algorithm>

int fibonacci (int n){
    if(n < 0) {
        throw "Only Positive Integers";
    }
    else if(n == 0 || n == 1){
        return 1;
    }
    else{
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int* recursion(int n){
    int* arr = new (std::nothrow) int[n];
    for(int i=0; i<n; i++){
        arr[i] = fibonacci(i);
    }
    return arr;
}

long long int* iteration(long long int n){
    long long int* arr = new (std::nothrow) long long int[n];
    for(int i=0; i<n; i++){
        if(i == 0 || i == 1) arr[i] = 1;
        else arr[i] = arr[i-1] + arr[i-2];
    }
    return arr;
}

int main(){
    long long int n ;
    std::cout << "Enter a number" << "\t";
    std::cin >> n;

    int arr[5]; 


    try{
        // auto start = std::chrono::high_resolution_clock::now();
        // int* recursive_array = recursion(n);
        // auto stop = std::chrono::high_resolution_clock::now();
        // std::cout << std::chrono::duration_cast<std::chrono::seconds>(stop-start).count() << '\n';

        auto start = std::chrono::high_resolution_clock::now();
        long long* iterative_array = iteration(n);
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << iterative_array[n-1] << '\n';
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << '\n';


        int arr[5] = {};
        std::cout << "Initialization: " << arr[1];
    }
    catch (std::string ex){
        std::cout << ex;
    }

    return 0;
}