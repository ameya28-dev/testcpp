#include <iostream>

class Rectangle{
    int width, height;

    public:
        Rectangle();
        Rectangle(int, int);

        void set_values(int, int); // not-inline member function

        int area(){    // inline member function
            return width*height;
        }         // possible complier optimization
};

void Rectangle::set_values(int x, int y){
    width = x;
    height = y;
}

Rectangle::Rectangle (){
    width = 0; height = 0;
}

Rectangle::Rectangle (int a, int b){
    width = a; height = b;
}

// Member Initialization
// Rectangle::Rectangle (int a, int b) : width(a) {height = b;}
// Here rectangle has a function body

// OR

// Rectangle::Rectangle (int a, int b) : width(a), height(b) {}

class Circle{
    double radius;

public:
    Circle(double r) {
        radius = r;
    }

    Circle(){
        radius = 10.0;
    }

    double circum(){
        return 3.14*radius*radius;
    }

};

class Cylinder{
    Circle base;
    double height;

public:
    Cylinder(double r, double h) : base(r), height(h) {}
    double volume() {
        return base.circum() * height;
    }
};

int main(){
    Rectangle rect0; // default constructor -> no parameters called when declared
    Rectangle rect(3,4); // object is initialized
    // rect.set_values(10,8);

    std::cout << rect0.area() << '\n';
    std::cout << rect.area() << '\n';


    Circle foo(10.0); // functional form
    Circle bar = 10.0; // assignment init
    Circle baz {30.0}; // uniform init
    Circle qux = {40.0}; // POD-like

    Circle cir1; // default constructor
    Circle cir2{}; // default constructor
    // Circle cir3(); // function declaration --> throws warning

    std::cout << cir1.circum() << '\n';
    std::cout << cir2.circum() << '\n';

    Cylinder cyl {10,20};
    std::cout << cyl.volume() << '\n';


    // Pointers
    Rectangle obj (3,4);
    Rectangle *a, *b, *c;
    a = &obj;
    b = new Rectangle(5,6);
    std::cout << "Size of Rectangle b: " << sizeof(b) << '\n';
    c = new Rectangle[2] {{2,3}, {3,6}};
    std::cout << "Size of Rectangle c: " << sizeof(c) << '\n';
    std::cout << "obj's area: " << obj.area() << '\n';
    std::cout << "*a's area: " << a->area() << '\n';
    std::cout << "*b's area: " << b->area() << '\n';
    std::cout << "c[0]'s area: " << c[0].area() << '\n';
    std::cout << "c[1]'s area: " << c[1].area() << '\n';
    delete b;
    delete[] c;
    return 0;
}