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

void play4() {
    int A[] = {2, 4, 5, 8, 1};
    int i;
    for (i = 0; i < 5; i++) {
        printf("Address of &A[i] = %p\n", &A[i]);
        printf("Address of A + i = %p\n", A + i);
        printf("Value of A[i] = %d\n", A[i]);
        printf("Value of *(A + i) = %d\n", *(A + i));
    }
}

int sumOfElements(int A[], int size) {
    // int A[] implicitly converts to int *A
    int i, sum = 0;
//    int size = sizeof(A)/ sizeof(A[0]);
    printf("SOE - Size of A = %lu, size of A[0] = %lu\n", sizeof(A), sizeof(A[0]));
    for (i = 0; i < size; i++) {
        sum += A[i]; // A[i] can be used *(A + i)
    }
    return sum;
}

void play5() {
    int A[] = {1, 2, 3, 4, 5};
    int size = sizeof(A)/ sizeof(A[0]);
    int total = sumOfElements(A, size); // A can be used &A[0]
    printf("Main - Size of A = %lu, size of A[0] = %lu\n", sizeof(A), sizeof(A[0]));
    printf("Sum of elements = %d\n", total);
}

void print(const char *C) {
//    C[0] = 'A';  // Error
    while (*C != '\0') {
        printf("%c", *C);
        C++;
    }
    printf("\n");
}

void play6() {
    char C[20] = "Aello";  // String gets stored in the space for array
    C[0] = 'H';  // Ok
//    char *C = "Aello";  // String gets stored as compile time constant
//    C[0] = 'H';  // Error
    print(C);
}

int main() {
    printf("Playground 1: \n");
    play1();

    printf("\nPlayground 2: \n");
    play2();

    printf("\nPlayground 3: \n");
    play3();

    printf("\nPlayground 4: \n");
    play4();

    printf("\nPlayground 5: \n");
    play5();

    printf("\nPlayground 6: \n");
    play6();

    return 0;
}