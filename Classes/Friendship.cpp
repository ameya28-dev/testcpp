#include <iostream>
using namespace std;

class Square;

class Rectangle {
    int width, height;
public:
    Rectangle() {}
    Rectangle(int x, int y) : width(x) , height(y) {}
    int area() {return width * height;}
    friend Rectangle duplicate (const Rectangle&); 
    // duplicate isn't a function of class Rectangle
    // It is only able to access private and protected members of Rectangle
    void convert(Square);
};

class Square{
    friend class Rectangle;
    private:
        int side;
    public:
        Square(int a) : side(a) {}
};

void Rectangle::convert(Square a){
    width = a.side;
    height = a.side;
}

Rectangle duplicate (const Rectangle& param) {
    Rectangle res;
    res.width = param.width;
    res.height = param.height;
    return res;
}

int main(){
    Rectangle foo;
    Rectangle bar(2,3);
    foo = duplicate(bar);
    cout << foo.area() << "\n";

    Rectangle rect;
    Square sqr(4);
    rect.convert(sqr);
    cout << rect.area() << '\n';

    return 0;
}