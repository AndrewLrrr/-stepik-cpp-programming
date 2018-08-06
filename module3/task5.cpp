/*
Добавьте в класс String реализацию конструктора копирования. Инвариант класса остается тем же (в size хранится размер
строки без завершающего 0 символа, str указывает на C-style строку, т. е. с завершающим нулевым символом).

Требования к реализации: вы можете заводить любые вспомогательные методы или функции, но не реализуйте заново методы из
предыдущих заданий — они уже реализованы. При реализации не нужно вводить или выводить что-либо. Реализовывать main не
нужно. Не используйте функции из cstdlib (malloc, calloc, realloc и free).
*/

#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
using namespace std;

struct String {
    String(const char *str = "")
            : size(strlen(str))
            , str(new char[size + 1])
    {
        strcpy(this->str, str);
    }

    String(size_t n, char c)
            : size(n)
            , str(new char[size + 1])
    {
        for (int i = 0; i < n; i++) {
            str[i] = c;
        }
        str[n] = '\0';
    }

    /* Реализуйте конструктор копирования */
    String(const String &other)
            : size(other.size)
            , str(new char[other.size + 1])
    {
        for (int i = 0; i <= other.size; i++) {
            str[i] = other.str[i];
        }
    }

    ~String() {
        delete[] str;
    }

    void append(String &other) {
        size_t old_size = size;

        resize(other.size + size);

        for (size_t i = old_size; i < size; i++)
            str[i] = other.str[i - old_size];

        str[size] = '\0';
    }

    void resize(size_t new_size) {
        char *new_str = new char[new_size + 1];

        strcpy(new_str, str);

        delete[] str;

        size = new_size;
        str = new_str;
    }

    size_t size;
    char *str;
};

int main() {
    String s1("Hello, world");
    cout << "s1: " << s1.str << " | size: " << s1.size << endl;

    String s2(s1);
    cout << "s2(s1): " << s2.str << " | size: " << s2.size << endl;

    String s3 = s1;
    cout << "s3 = s1: " << s2.str << " | size: " << s2.size << endl;

    return 0;
}