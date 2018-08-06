/*
Конструкторов у структуры может быть несколько. Для строки может оказаться полезным заполняющий конструктор (например,
чтобы создать строку пробелов). Заполняющий конструктор принимает число и символ, и создает строку с заданным
количеством повторений переданного символа. Условия налагаемые на реализацию конструктора те же самые (в поле size
размер без учета завершающего 0 символа, в поле str C-style строка, т.е. с завершающим 0 символом). Кроме конструктора
в этой задаче вам нужно также реализовать и деструктор, который освободит выделенную память.

Требования к решению: в этом задании не нужно вводить или выводить что-либо, не нужно реализовывать функцию main. Для
работы с памятью не используйте функции из cstdlib (malloc, calloc, realloc и free).
*/

#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
using namespace std;

struct String {
    String(size_t n, char c)
            : size(n)
            , str(new char[size + 1])
    {
        for (int i = 0; i < n; i++) {
            str[i] = c;
        }
        str[n] = '\0';
    }

    ~String() {
        delete[] str;
    }

    size_t size;
    char *str;
};

int main() {
    String s1 = String(5, 's');
    cout << "String1.str: " << s1.str << endl;
    cout << "String1.size: " << s1.size << endl;
    String s2 = String(10, 'e');
    cout << "String2.str: " << s2.str << endl;
    cout << "String2.size: " << s2.size << endl;

    return 0;
}