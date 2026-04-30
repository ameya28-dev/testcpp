#include <stdio.h>

struct student {
    char* name;
};

typedef struct _person {
    const char* name;
    int age;
} Person;

struct student s;

struct student fun() {
    s.name = "newton";
    printf("%s\n", s.name);
    s.name = "alan";
    return s;
}

int main() {
    struct student m = fun();
    printf("%s\n", m.name);
    m.name = "turing";
    printf("%s\n", s.name);
    printf("%s\n", m.name);

    Person p;
    p.name = "Lorena Rae";
    p.age  = 31;
    printf("%s\n", p.name);
    printf("%d\n", p.age);

    struct _person p2;
    p2.name = "Ava Allan";
    p2.age  = 25;
    printf("%s\n", p2.name);
    printf("%d\n", p2.age);

    return 0;
}
