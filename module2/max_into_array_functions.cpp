#include <iostream>
using namespace std;

int *max_element(int *p, int *q) {
    int *pmax = p;
    for (; p != q; p++) {
        if (*p > *pmax) {
            *pmax = *p;
        }
    }
    return pmax;
}

bool max_element_p(int *p, int *q, int *res) {
    if (p == q) {
        return false;
    }
    *res = *p;
    for (; p != q; p++) {
        if (*p > *res) {
            *res = *p;
        }
    }
    return true;
}

bool max_element_pp(int *p, int *q, int **res) {
    if (p == q) {
        return false;
    }
    *res = p;
    for (; p != q; p++) {
        if (*p > **res) {
            *res = p;
        }
    }
    return true;
}

int main() {
    int m[10] = {1, 4, 5, 2, 3, 9, 6, 7, 8};
    int max = 0;
    int *pmax = 0;

    int *res1 = max_element(m, m + 10);
    bool res2 = max_element_p(m, m + 10, &max);
    bool res3 = max_element_pp(m, m + 10, &pmax);

    std::cout << "Maximum int = " << *res1 << endl;

    if (res2) {
        cout << "Maximum pointer = " << max << endl;
    } else {
        cout << "Array is empty..." << endl;
    }

    if (res3) {
        cout << "Maximum pointer pointer = " << max << endl;
    } else {
        cout << "Array is empty..." << endl;
    }
}