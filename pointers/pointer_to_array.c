#include <stdio.h>

void pointer_to_array() {
    int A[] = {2, 4, 5, 8, 1};
    int i;
    for (i = 0; i < 5; i++) {
        printf("Address of &A[i] = %p\n", &A[i]);
        printf("Address of A + i = %p\n", A + i);
        printf("Value of A[i] = %d\n", A[i]);
        printf("Value of *(A + i) = %d\n", *(A + i));
    }
}