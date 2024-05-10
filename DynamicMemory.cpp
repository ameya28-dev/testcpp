#include <iostream>

int main(){
    int* foo;
    foo = new (std::nothrow) int [5];
    if(foo == nullptr){
	std::cout << "Null pointer\n";
	return 0;
    }
    
    std::cout << "No null pointer\n";

    int i, n;
    int* p;
    std::cout << "How many numbers would you like to type? ";
    std::cin >> i;
    
    p = new (std::nothrow) int[i];
    if(p == nullptr){
        std::cout << "Error: memory could not be allocated";
    }
    else{
        for(n = 0; n < i; n++){
        std::cout <<  "Enter number: ";
        std::cin >> p[n];
        }

        std::cout << "You have entered: ";
        for (n=0; n<i; n++)
        std::cout << p[n] << ", ";
        }

        delete[] p;

    return 0;
}
