#include "sprite.h"
#include <iostream>

class Renderer {
public:
    Renderer() {
        std::cout << &Genesis::Sprites::Grass << std::endl;
    }
};

Renderer renderer = Renderer();
