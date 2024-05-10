#include <iostream>
#include <array>

void increment_all (int* start, int* end);
void print_all (const int* start, const int* end);

void increment_all(int arr[], int size){
    for(int i = 0; i < size; i++){
        arr[i]++;
    }
}

void print_all(int arr[], int size){
    for(int i = 0; i < size; i++){
        std::cout << arr[i] << std::endl;
    }
}

void increase (void* data, int psize){
    if (psize == sizeof(char))
    {
        char* pchar = (char*) data;
        (*pchar)++;
    }
    if (psize == sizeof(int))
    {
        int* pint = (int*) data;
        (*pint)++;
    }
}

int addition (int a, int b){
    return a+b;
}

int subtraction (int a, int b){
    return a-b;
}

int operation (int x, int y, int (*functocall)(int, int)){
    int g;
    g = (*functocall)(x,y);
    return g;
}

int main(){

    // Intro
    int firstValue = 5, secondValue = 15;
    int * p1, * p2;

    p1 = &firstValue;
    p2 = &secondValue;

    *p1 = 10;
    *p2 = *p1;
    p1 = p2;
    *p1 = 20; 

    std::cout << "First value is " << firstValue << "\n";
    std::cout << "Second value is " << secondValue << "\n";

    // Pointers and Arrays
    int numbers[5];
    int* p;
    p = numbers;
    std::cout << p << '\n';
    *p = 10;
    p++, *p = 20;
    std::cout << p << '\n';
    p = &numbers[2]; *p = 30;
    p = numbers + 3; *p = 40;
    p = numbers; *(p+4) = 50;

    for(int i = 0; i < 5; i++){
        std::cout << numbers[i] << '\t';
    }

    std::cout << '\n';

    int myvar;
    int * foo = &myvar;
    int * bar = foo;

    // Constants
    int x; int y = 10;
    const int* ptr = &y;
    x = *ptr;

    int numbers1[] = {10,20,30};
    increment_all(numbers1, sizeof(numbers1)/sizeof(int));
    print_all(numbers1, sizeof(numbers1)/sizeof(int));
    increment_all(numbers1, numbers1+3);
    print_all(numbers1,  numbers1+3);

    int a = 10;
    int* p5 = &a; // non - const pointer to non-const int
    p5++; (*p5)++;
    const int* p6 = &a; // non-const pointer to const int
    // (*p6)++ -->  not allowed
    p6++;
    int* const p3 = &a; // const pointer to non-const int
    (*p3)++; // p3++ --> not allowed
    const int* const p4 = &a; // const pointer to const int
    // (*p4)++; p4++; --> not allowed

    const int* pa = &a; 
    int const* pb = &a;

    // Pointers and string literals
    const char * hello = "Hello";

    // Pointers to pointers
    char aa;
    char* b; char** c;
    aa = 'z';
    b = &aa;
    c = &b;

    // void pointers
    char m = 'x';
    int n = 1609;
    increase(&m, sizeof(m));
    increase(&n, sizeof(n));
    std::cout << m << '\t' << n << '\n';

    // Invalid pointers and null pointers
    int* uninitializedpointer;
    int myArray[10]; int* outofboundpointer = myArray+20;
    uninitializedpointer = 0;
    outofboundpointer = nullptr;
    std::cout << *uninitializedpointer << '\t' << *outofboundpointer << '\n';

    // Pointers to functions
    int (* minus)(int, int) = subtraction;
    int i = operation(7, 5 ,addition);
    int j = operation(20, i, minus);
    std::cout << "Output: " << j << '\n';
  
    return 0;
}

void increment_all(int* start, int* end){
    int* current = start;
    while (current != end)
    {
        (*current)++;
        current++;
    }
    
}

void print_all (const int* start, const int* end){
    using namespace std;
    const int* current = start;
    while (current != end)
    {
        cout << *current <<'\n';
        current++;
    }
    
}