#include <stdio.h>

void pointer() {
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