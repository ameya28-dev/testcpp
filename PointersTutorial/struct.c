#include <stdio.h>

struct student
{
    char *name;
};

struct student s;

struct student fun()
{
    s.name = "newton";
    printf("%s\n", s.name);
    s.name = "alan";
    return s;
}

int main(){
    struct student m = fun();
    printf("%s\n", m.name);
    m.name = "turing";
    printf("%s\n", s.name);
    printf("%s\n", m.name);
    return 0;
}