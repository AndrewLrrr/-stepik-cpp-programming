/*
Напишите функцию, которая принимает на вход целочисленную матрицу M (другими словами, просто двумерный целочисленный
массив) размера rows×cols, и возвращает транспонированную матрицу MT (тоже двумерный целочисленный массив) размера
cols×rows. Если в M на пересечении i-ой строки и j-ого столбца стояло число x, то на пересечении j-ой строки и i-ого
столбца в матрице MT тоже будет стоять число x, или другими словами MT[j][i]=M[i][j].

Обратите внимание, что вам неизвестно, каким именно способом выделялась память для массива M. Выделять память под
массив MT можете любым удобным вам способом. Изменять исходную матрицу нельзя.

Требования к реализации: при выполнении этого задания вы можете определять любые вспомогательные функции. Вводить или
выводить что-либо не нужно. Реализовывать функцию main не нужно.
*/

#include <iostream>
using namespace std;

void free_array2d(int **m, unsigned rows, unsigned cols) {
    delete m[0];
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

int **transpose(const int *const *m, unsigned rows, unsigned cols) {
    int **m_t = create_array2d(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m_t[j][i] = m[i][j];
        }
    }

    return m_t;
}

int main() {
    int **m = create_array2d(3, 3);

    for (size_t i = 0; i < 3; i++) {
        size_t step = (i * 2);
        for (size_t j = 0; j < 3; j++) {
            m[i][j] = i + (j + 1) + step;
        }
    }

    cout << "Base matrix: " << endl;
    for (size_t i=0; i < 3; i++) {
        for (size_t j=0; j < 3; j++) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;

    int **m_t = transpose(m, 3, 3);

    free_array2d(m, 3, 3);

    cout << "Transposed matrix: " << endl;
    for (size_t i=0; i < 3; i++) {
        for (size_t j=0; j < 3; j++) {
            cout << m_t[i][j] << ' ';
        }
        cout << endl;
    }

    free_array2d(m_t, 3, 3);

    return 0;
}