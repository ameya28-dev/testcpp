#include <iostream>
#include <sstream>

struct product
{
    int weight; double price;
} apple, banana, melon;

struct {
    int height;
} person ;


struct movies_t
{
    std::string title; int year;
};

void printmovie(movies_t movie){
    std::cout << movie.title;
    std::cout << " (" << movie.year <<") \n";
}


int main(){
    std::string mystr;

    movies_t amovie;
    movies_t* pmovie;
    pmovie = &amovie;

    std::cout << "Enter title: ";
    getline(std::cin, pmovie->title);
    std::cout << "Enter year: ";
    // getline(std::cin, mystr);
    // std::stringstream(mystr) >> yours.year;
    std::cin >> pmovie->year;


    // std::cout << "My favourite movie is:\n";
    // printmovie(mine);
    // std::cout << "And yours is:\n";
    // printmovie(yours);
    
    std::cout << "\nYou have entered:\n";
    std::cout << pmovie->title;
    std::cout << " (" << pmovie->year << ")\n";

    return 0;
}
