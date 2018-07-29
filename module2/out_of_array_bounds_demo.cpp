#include <iostream>
using namespace std;

int foo() {
    cout << "Hello, hacker!" << endl;
    return 2;
}

int bar(int a) {
    int *m[1];
    m[a] = (int *) &foo;
    return 1;
}

int main() {
    int a = 0;
    cout << "For explore input 3" << endl;
    cin >> a;
    int b = bar(a);
    cout << "bar(a) return value: " << b << endl;
    return 0;
}