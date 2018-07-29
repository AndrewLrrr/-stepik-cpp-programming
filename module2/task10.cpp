/*
Реализуйте функцию swap_min, которая принимает на вход двумерный массив целых чисел, ищет в этом массиве строку,
содержащую наименьшее среди всех элементов массива значение, и меняет эту строку местами с первой строкой массива.

Подумайте, как обменять строки массива, не обменивая элементы строк по-отдельности.

Требования к реализации: при выполнении этого задания вы можете определять любые вспомогательные функции. Вводить или
выводить что-либо не нужно. Реализовывать функцию main не нужно.
*/


#include <iostream>
using namespace std;

void free_array2d(int **m, int *first_m) {
    delete first_m;
    delete m;
}

int **create_array2d(unsigned rows, unsigned cols) {
    int **m = new int *[rows];
    m[0] = new int[rows * cols];
    for (int i = 1; i != rows; ++i) {
        m[i] = m[i - 1] + cols;
    }

    return m;
}

void swap_min(int *m[], unsigned rows, unsigned cols) {
    int min = m[0][0];
    int *first_pointer = m[0];
    int *row_pointer = m[0];
    int index = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (min > m[i][j]) {
                min = m[i][j];
                row_pointer = m[i];
                index = i;
            }
        }
    }

    if (row_pointer != first_pointer) {
        m[0] = row_pointer;
        m[index] = first_pointer;
    }
}

int main() {
    int **m = create_array2d(3, 3);
    int *first_m = m[0];

    for (size_t i = 0; i < 3; i++) {
        size_t step = (i * 2);
        for (size_t j = 0; j < 3; j++) {
            m[i][j] = 9 - (i + j + step);
        }
    }

    cout << "Base array: " << endl;
    for (size_t i=0; i < 3; i++) {
        for (size_t j=0; j < 3; j++) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;

    swap_min(m, 3, 3);

    cout << "Swapped array: " << endl;
    for (size_t i=0; i < 3; i++) {
        for (size_t j=0; j < 3; j++) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }

    free_array2d(m, first_m);

    return 0;
}