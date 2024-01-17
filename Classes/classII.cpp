#include <iostream>

class CVector
{
public:
    int x, y;
    CVector(){};
    CVector(int a, int b) : x(a), y(b){};
    CVector operator+(const CVector &);
    CVector &operator=(const CVector &);
};

CVector &CVector::operator=(const CVector &params)
{
    x = params.x;
    y = params.y;
    return *this;
}

CVector CVector::operator+(const CVector &param)
{
    CVector temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return temp;
}

CVector operator*(const CVector &lhs, const CVector &rhs)
{
    CVector temp;
    temp.x = lhs.x * rhs.x;
    temp.y = lhs.y * rhs.y;
    return temp;
}

class Dummy
{
public:
    static int n;
    Dummy() { n++; };
    bool isitme(Dummy &param);

private:
    int y;
};

int Dummy::n = 0;

bool Dummy::isitme(Dummy &param)
{
    if (&param == this)
        return true;
    else
        return false;
}

class MyClass
{
public:
    int x;
    MyClass(int v) : x(v){}
    // int get() const {return x;}
    const int& get() const {return x;}
    int& get() {return x;}
};

int main()
{
    // Operator Overloading
    CVector foo(3, 1);
    CVector bar(4, 5);
    CVector zap;

    CVector result = foo + bar;
    CVector product = foo * bar;

    // this
    zap = bar;

    std::cout << result.x << "," << result.y << '\n';
    std::cout << product.x << "," << product.y << '\n';

    Dummy a;
    Dummy *b = &a;
    Dummy c;
    if (b->isitme(a))
        std::cout << "Yes, it is me" << '\n';
    if (c.isitme(a))
        std::cout << "No, it is not me" << '\n';

    // Static members
    Dummy dummy;
    Dummy dummies[5];
    std::cout << dummy.n << '\n';
    Dummy *dummyptr = new Dummy;
    std::cout << Dummy::n << '\n';

    Dummy::n = 10;
    std::cout << dummy.n << '\n';
    std::cout << dummies[2].n << '\n';
    std::cout << dummyptr->n << '\n';
    delete dummyptr;

    // Const Member functions

    const MyClass myclass1(10);
    MyClass myclass2(20);
    std::cout << myclass1.x << '\n';
    int y = myclass1.get();
    y = myclass2.get();

    MyClass myclass3(30);
    const MyClass myclass4 (40);
    myclass3.get() = 15;
    int number = myclass4.get();

    return 0;
}