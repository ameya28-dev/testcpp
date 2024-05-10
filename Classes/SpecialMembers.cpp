#include <iostream>
using namespace std;

class Example
{
private:
    string data;

public:
    Example(const string &str) : data(str) {}
    Example() {} // Default constructor
    const string &content() const { return data; }
};

class Example1
{
    string *ptr;

public:
    Example1() : ptr(new string) {}
    Example1(const string &ptr) : ptr(new string(ptr)) {}
    ~Example1() { delete ptr; }

    // Copy constructor
    // Deep Copy is made here
    // x.content() returns a new string whose memory is allocated to members of copy objects
    Example1(const Example1 &x) : ptr(new string(x.content())) {}

    // Example1& operator= (const Example1& x){
    //     delete ptr;                     // deletes currently pointed string
    //     ptr = new string(x.content());  // allocate space for new string, and copy
    //     return *this;
    // }

    // OR
    // since ptr is not const, reutilize the same string object
    Example1& operator= (const Example1& x){
        *ptr = x.content();
        return *this;
    }

    // access content
    const string &content() const { return *ptr; }
};

// Move constructor

// Copy Constructor
class MyClass
{
public:
    int a, b;
    string c;
};

// Implicitly a copy constructor is called which might do something similar to this
// Performs a shallow copy, roughly equivalent to:
// MyClass::MyClass (const MyClass& x) : a(x.a), b(x.b), c(x.c) {}

int main()
{
    Example foo;
    Example bar("BAR");

    cout << "bar's content:\t" << bar.content() << '\n';

    Example1 foo1;
    Example1 bar1("BAR 1");
    cout << "bar1's content:\t" << bar1.content() << '\n';

    Example1 foo2("Example");
    Example1 bar2 = foo2;

    MyClass m1;
    MyClass m2(m1);  // object initialization: copy constructor called
    MyClass m3 = m1; // object initialization: copy constructor called
    m1 = m2;         // already initialized: copy operator called

    return 0;
}