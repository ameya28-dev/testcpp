#include <stdio.h>

int main(){
    char *p = NULL;
    char *q = 0;


    if(p){
        printf(" p ");
    }
    else printf("nullp");

    if(q) printf("q\n");
    else printf(" nullq\n");

    return 0;
}