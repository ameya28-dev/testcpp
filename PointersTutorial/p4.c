#include <stdio.h>

int main()
{
    int arri[] = {1, 2, 3};
    int* ptr1 = arri;

    char arrc[] = {1,2,3};
    char *ptrc =arrc; 

    printf("sizeof arri[] = %d\n", sizeof(arri));
    printf("sizeof ptr1[] = %d\n", sizeof(ptr1));
    printf("sizeof arrc[] = %d\n", sizeof(arrc));
    printf("sizeof ptrc[] = %d\n", sizeof(ptrc));
}