#include <stdio.h>

void pointer_to_pointer() {
    int x = 5;
    int *p = &x;
    *p = 6;
    int **q = &p;
    int ***r = &q;
    printf("x = %d\n", x);
    printf("p = %p\n", p);
    printf("*p = %d\n", *p);
    printf("q = %p\n", q);
    printf("*q = %p\n", *q);
    printf("**q = %d\n", *(*q));
    printf("r = %p\n", r);
    printf("*r = %p\n", *r);
    printf("**r = %p\n", *(*r));
    printf("***r = %d\n", *(*(*r)));
    ***r = 10;
    printf("x = %d\n", x);
    **q = *p + 2;
    printf("x = %d\n", x);
}