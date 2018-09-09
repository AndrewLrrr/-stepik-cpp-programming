#include <stdio.h>

void increment(int *a) {
    *a = *a + 1;
}

void pointer_arithmetic() {
    int a = 10;
    printf("a before = %d\n", a);
    increment(&a);
    printf("a after = %d\n", a);
}