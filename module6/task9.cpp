/*
Реализуйте функцию array_size, которая возвращает размер массива, переданного в качестве параметра. Функция должна
работать только для массивов! Т. е. если функции передать указатель, должна произойти ошибка компиляции. Примеры:

int ints[] = {1, 2, 3, 4};
int *iptr = ints;
double doubles[] = {3.14};
array_size(ints); // вернет 4
array_size(doubles); // вернет 1
array_size(iptr); // тут должна произойти ошибка компиляции

Hint: в одной из первых недель мы вам показывали трюк с передачей массивов только заданного размера в функцию (передача
массива по ссылке), совместите его с вашими знаниями о шаблонах.
*/

#include <stdio.h>
#include <cstddef> // size_t

template<class T, size_t K>
size_t array_size(T (&a)[K]) {
    return K;
}

int main() {
    int ints[] = {1, 2, 3, 4};
    int *iptr = ints;
    double doubles[] = {3.14};
    printf("%lu\n", array_size(ints)); // вернет 4
    printf("%lu\n", array_size(doubles)); // вернет 1
    // array_size(iptr); // тут должна произойти ошибка компиляции
}