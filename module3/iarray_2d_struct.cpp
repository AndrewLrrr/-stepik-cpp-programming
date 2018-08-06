#include <iostream>
using namespace std;

int **create_array2d(unsigned rows, unsigned cols) {
    int **m = new int *[rows];
    m[0] = new int[rows * cols];
    for (int i = 1; i != rows; ++i) {
        m[i] = m[i - 1] + cols;
    }

    return m;
}

struct IntArray2D {
    int &get(size_t i, size_t j) {
        return data[i * cols + j];
    }

    void set(size_t i, size_t j, int v) {
        data[i * cols + j] = v;
    }

    size_t rows;
    size_t cols;
    int *data;
};

int main() {
    int rows = 3;
    int cols = 3;
    IntArray2D a = {rows, cols, *create_array2d(rows, cols)};

    for (size_t i = 0; i < 3; i++) {
        size_t step = (i * 2);
        for (size_t j = 0; j < 3; j++) {
            a.set(i, j, (i + (j + 1) + step));
        }
    }

    cout << "IntArray2D rows: " << a.rows << endl;
    cout << endl;

    cout << "IntArray2D cols: " << a.cols << endl;
    cout << endl;

    cout << "IntArray2D data: " << endl;
    for (size_t i=0; i < 3; i++) {
        for (size_t j=0; j < 3; j++) {
            cout << a.get(i, j) << ' ';
        }
        cout << endl;
    }
}