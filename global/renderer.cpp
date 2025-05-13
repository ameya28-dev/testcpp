#include <iostream>

#include "sprite.h"

class Renderer {
   public:
    Renderer() {
        std::cout << &Genesis::Sprites::Grass << std::endl;
    }
};

Renderer renderer = Renderer();