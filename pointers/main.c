#include <stdio.h>
#include "pointers.h"

int main() {
    printf("Simple pointer example: \n");
    pointer();

    printf("\nPointer to pointer: \n");
    pointer_to_pointer();

    printf("\nPointer arithmetic: \n");
    pointer_arithmetic();

    printf("\nPointer to array: \n");
    pointer_to_array();

    printf("\nArray as function argument: \n");
    array_as_func_argument();

    printf("\nPointer to char array: \n");
    pointer_to_str();

    printf("\nPointer to 2d array: \n");
    pointer_to_2d_array();

    return 0;
}