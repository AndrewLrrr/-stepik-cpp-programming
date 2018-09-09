#include <stdio.h>

void print(const char *C) {
    // C[0] = 'A';  // Error
    while (*C != '\0') {
        printf("%c", *C);
        C++;
    }
    printf("\n");
}

void pointer_to_str() {
    char C[20] = "Aello";  // String gets stored in the space for array
    C[0] = 'H';  // Ok
    // char *C = "Aello";  // String gets stored as compile time constant
    // C[0] = 'H';  // Error
    print(C);
}