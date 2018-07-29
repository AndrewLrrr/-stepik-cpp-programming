#include <stdio.h>

void play1() {
    int a = 1025;
    int *p;
    p = &a;
    printf("Size of int in bytes = %lu\n", sizeof(int));
    printf("Pointer address = %p, value = %d\n", p, *p);
    // 1025 = [00000000] [00000000] [00000100] [00000001] <- int Pointer
    printf("Pointer + 1 address = %p, value = %d\n", p + 1, *(p + 1));
    char *c;
    c = (char *) p; // typecasting
    printf("Size of char in bytes = %lu\n", sizeof(char));
    printf("Char pointer address = %p, value = %d\n", c, *c);
    // 1 = [00000001] <- char Pointer
    printf("Char pointer + 1 address = %p, value = %d\n", c + 1, *(c + 1));
    // 4 = [00000100] <- char Pointer + 1
}

void play2() {
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

void increment(int *a) {
    *a = *a + 1;
}

void play3() {
    int a = 10;
    printf("a before = %d\n", a);
    increment(&a);
    printf("a after = %d\n", a);
}

int main() {
    printf("Playground 1: \n");
    play1();

    printf("\nPlayground 2: \n");
    play2();

    printf("\nPlayground 3: \n");
    play3();

    return 0;
}