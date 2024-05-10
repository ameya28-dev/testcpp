#include <iostream>
using namespace std;

class Polygon {
    protected:
        int width, height;
    public:
        void set_values (int a, int b){
            width = a, height = b;
        }
};

class Rectangle : public Polygon {
    public:
        int area (){
            return width * height;
        }
};

class Triangle : public Polygon {
    public:
        double area (){
            return width * height * 0.5;
        }
};

int main(){
    return 0;
}