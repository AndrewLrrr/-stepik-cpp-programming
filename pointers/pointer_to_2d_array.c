#include <stdio.h>

void pointer_to_2d_array() {
    int A[2][3];
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 4;
    A[1][1] = 5;
    A[1][2] = 6;

    int (*p)[3] = A;
    printf("%p == %p\n", p, &p[0]);
    printf("%p == %p == %p\n", *p, p[0], &p[0][0]);
    printf("%p == %p\n", p+1, &p[1]);
    printf("%p == %p == %p\n", *(p+1), p[1], &p[1][0]);
    printf("%p == %p == %p\n", *(p+1)+2, p[1]+2, &p[1][2]);
    printf("%d\n", *(*p+1));
    printf("%d == %d == %d\n", *(*p+5), *(p[1]+2), *(*(p+1)+2));
}
