#include <stdio.h>

void foo() {
    FILE * f = fopen("p1.c", "r");
}

void fun(int* ptr) {
    *ptr = 30;
}

int main() {
    int y = 20;
    fun(&y);
    printf("%d", y);

    return 0;
}
