#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    string name;
    ifstream input("input.txt");
    input >> name;

    cout << "My name is: " << name << endl;

    ofstream output("output.txt");
    output << "Hi, my name is " << name << endl;
    return 0;
}