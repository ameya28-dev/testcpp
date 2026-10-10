#include <cstdlib>
#include <iostream>
#include <memory>

class Base {
public:
    void sing() {
        std::cout << identity << " can sing!!\n";
    }

protected:
    void dance() {
        std::cout << identity << " can dance!!\n";
    }

private:
    static constexpr auto identity = "base";

    void draw() {
        std::cout << identity << " can draw!!\n";
    }
};

int main() {
    /*  Access Modifiers   */
    Base b;
    b.sing();
    // dance() and draw() are not accessible because they are not public
    // b.dance();
    // b.draw();

    /* Public Inheritance*/
    {
        class Derived : public Base {
            void init() {
                sing();
                dance();
                /* Private methods of Base are not available in AllDerived */
                // draw();
            }
        };

        class DerivedAgain : public Derived {
            void init() {
                sing();
                dance();
                /* no named collision because init() in Derived is private to DerivedAgain*/
            }
        };

        Derived d;
        d.sing();

        DerivedAgain dA;
        dA.sing();
    }

    /* Private Inheritence*/
    {
        class Derived : private Base {
        public:
            void hello() {
                std::cout << identity << " says Hi!!\n";
            }

        protected:
            void bye() {
                std::cout << identity << " says bye!!\n";
            }

        private:
            const char* identity = "Derived";

            void init() {
                sing();
                dance();
                // private functions of Base are not accessible
                // draw();
            }
        };

        class DerivedAgain : private Derived {
            void init() {
                // sing();
                // dance();
                // draw();

                // draw() is private to Base
                // sing() and dance() is modified to private for Derived
                // Hence none of these methods are accessible in this class

                /// Newly added public or protected members are still accessible to child classes
                hello();
                bye();
            }
        };

        Derived d;
        // Even though sing() is public in Base
        // Since the Derived is privately inherited from Base
        // public and protected methods of Base become private to Derived
        // d.sing();

        // hello() is accessible because it is public to Derived
        d.hello();
        // bye() is not as it is protected
        // d.bye();

        [[maybe_unused]] DerivedAgain dA;
    }

    /* Protected Inheritence */
    {
        class Derived : protected Base {
        public:
            void hello() {
                std::cout << identity << " says Hi!!\n";
            }

        protected:
            void bye() {
                std::cout << identity << " says bye!!\n";
            }

        private:
            const char* identity = "Derived";

            void init() {
                // sing() and dance() have been modified to protected
                sing();
                dance();
                // private functions of Base are not accessible
                // draw();
            }
        };

        [[maybe_unused]] Derived d;

        // Not accessible because of protected
        // d.sing();
        // d.dance();

        class DerivedPublic : public Derived {
            void init() {
                // sing() and dance() are still protected
                sing();
                dance();
                // hello() is public
                hello();
                // bye() is protected
                bye();
            }
        };

        class DerivedProtected : protected Derived {
            void init() {
                // all of these become protected
                sing();
                dance();
                hello();
                bye();
            }
        };

        class DerivedPrivate : private Derived {
            void init() {
                // all of these become private
                sing();
                dance();
                hello();
                bye();
            }
        };

        DerivedPublic dPu;
        dPu.hello();

        [[maybe_unused]] DerivedProtected dPro;
        // dPro.hello();

        [[maybe_unused]] DerivedPrivate dPri;
        // dPri.hello();
    }

    auto u = std::make_unique<int>(5);
    auto s = std::make_shared<int>(5);

    std::cout << "Size of std::unique_ptr: " << sizeof(u) << '\n';
    std::cout << "Size of std::shared_ptr: " << sizeof(s) << '\n';

    struct FreeDeleter {
        void operator()(void* ptr) {
            free(ptr);
        }
    };

    auto ptr = std::unique_ptr<void, FreeDeleter>(malloc(sizeof(int)*5));
}
