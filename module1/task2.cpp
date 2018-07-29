// Реализуйте макрос MAX от трёх параметров, который присваивает целочисленной (int) переменной,
// переданной в качестве третьего аргумента, наибольшее из значений, переданных в первых двух аргументах

#include <iostream>
using namespace std;

#define MAX(x, y, r) { \
    int f = 0, s = 0; \
    f = (x); \
    s = (y); \
    r = (f > s) ? f : s; \
}

int main() {
    int a = 10;
    int b = 20;
    int c = 0;
    MAX(a, b, c);
    cout << c << endl;
    MAX(a += b, b, c);
    cout << c << endl;
}