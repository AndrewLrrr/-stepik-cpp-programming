#include <stdio.h>

int sum_of_elements(int *A, int size) {
    // int A[] implicitly converts to int *A
    int i, sum = 0;
    // int size = sizeof(A)/ sizeof(A[0]);
    printf("SOE - Size of A = %lu, size of A[0] = %lu\n", sizeof(A), sizeof(A[0]));
    for (i = 0; i < size; i++) {
        sum += A[i]; // A[i] can be used *(A + i)
    }
    return sum;
}

void array_as_func_argument() {
    int A[] = {1, 2, 3, 4, 5};
    int size = sizeof(A)/ sizeof(A[0]);
    int total = sum_of_elements(A, size); // A can be used &A[0]
    printf("Main - Size of A = %lu, size of A[0] = %lu\n", sizeof(A), sizeof(A[0]));
    printf("Sum of elements = %d\n", total);
}
