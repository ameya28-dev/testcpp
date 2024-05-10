#include <iostream>

enum colors_t {black = -10, blue, green, cyan , red, yellow, orange, violet, white};

enum class Color {black, blue, green, cyan , red, yellow, orange, violet, white};
enum class Color2 {black, blue, green, cyan , red, yellow, orange};
enum class People {Good, Bad};

enum Gender  {Male, Female};

enum Colors {Red, Blue};

int main(){
    colors_t mycolor;

    mycolor = green;
    if(mycolor == red) {
        mycolor = yellow;
        std::cout  << mycolor << '\n';
    }
    else {
        std::cout << mycolor << '\n';
    }

    for(int i =  black; i <= white; i++){
        std::cout << i << '\t';
        colors_t c = static_cast<colors_t>(i);
    }

    Gender gender = Male; Colors colors = Red;

    if(gender == colors) std::cout << '\n' << "Equal" << '\n';

    Color color;
    color = Color::green;
    if(color == Color::black) color = Color::green;

    int green = 10;

    Color x  = Color::green;
    Color2 y = Color2::green;

    return 0;
}