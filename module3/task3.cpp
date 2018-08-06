/*
Реализованные в предыдущих заданиях конструкторы и деструктор берут на себя работу по управлению ресурсами. Теперь
можно дополнить структуру String различными полезными методами.

Для работы со строками можно придумать множество полезных методов (подумайте, какие методы пригодились бы вам, и чего
вам не хватает для их реализации). Примером такого метода может послужить метод append — он добавляет копию
строки-аргумента в конец текущей строки (т.е. в конец строки, у которой он был вызван).

String s1("Hello,");
String s2(" world!");

s1.append(s2); // теперь s1 хранит "Hello, world!"
Ваша задача реализовать метод append.

При выполнении задания будьте аккуратны при работе с памятью — при вызове метода не должно возникать утечек памяти.
Кроме того, не забудьте, что size хранит размер без учета завершающего 0 символа.

Требования к реализации: при реализации вы можете заводить любые вспомогательные функции и методы. В шаблоне вы увидите
объявления уже известных вам конструкторов и деструкторов, реализовывать их заново не нужно, они уже реализованы.
Вводить или выводить что-либо не нужно. Реализовывать main не нужно. Для работы с памятью не используйте функции из
cstdlib (malloc, realloc, calloc и free).

Кроме того, ваша реализация должна корректно работать в следующем тесте:

String s("Hello");
s.append(s); // теперь s хранит "HelloHello"
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

    ~String() {
        delete[] str;
    }

    /* Реализуйте этот метод. */
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
    String s1 = String("Hello, ");
    String s2 = String("world!");
    String s3 = String(" How are you filling?");

    cout << "s1: " << s1.str << " | size: " << s1.size << endl;
    cout << "s2: " << s2.str << " | size: " << s2.size << endl;
    cout << "s3: " << s3.str << " | size: " << s3.size << endl;

    s1.append(s2);
    cout << "s1.append(s2): " << s1.str << " | size: " << s1.size << endl;

    s1.append(s3);
    cout << "s1.append(s3): " << s1.str << " | size: " << s1.size << endl;

    return 0;
}