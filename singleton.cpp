#include <iostream>
// class Singleton {
//    public:
//     static Singleton& get() {
//         return s_instance;
//     }

//    private:
//     Singleton() {}

//     static Singleton s_instance;
// };

class StaticClass {
   public:
    StaticClass() { value = 0; }
    StaticClass(int val) { value = val; }
    int get() const { return value; }
    void update(int val) const { value = val; }
    void print() const { std::cout << value << std::endl; }

   private:
    static int value;
};

int StaticClass::value;

int main() {
    StaticClass s1;

    s1.update(2);

    StaticClass s2(3);

    s1.print();
    s2.print();

    return 0;
}