// Определите только функцию power, где
// x - число, которое нужно возвести в степень
// p - степень, в которую нужно возвести x

#include <iostream>
using namespace std;

int power(int x, unsigned p) {
    int answer = 1;
    int i;
    for (i = p; i > 0; i--) {
        answer *= x;
    }
    return answer;
}

int main() {
    int x = 0;
    unsigned p = 0;

    cout << "Enter 2 integers:\n";
    cin >> x >> p;
    cout << power(x, p) << endl;

    return 0;
}
