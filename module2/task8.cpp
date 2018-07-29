/*
Реализуйте функцию getline, которая считывает поток ввода посимвольно, пока не достигнет конца потока или не встретит
символ переноса строки ('\n'), и возвращает C-style строку с прочитанными символами.

Обратите внимание, что так как размер ввода заранее неизвестен, то вам нужно будет перевыделять память в процессе
чтения, если в потоке ввода оказалось больше символов, чем вы ожидали.

Память, возвращенная из функции будет освобождена оператором delete[]. Символ переноса строки ('\n') добавлять в строку
не нужно, но не забудьте, что в конце C-style строки должен быть завершающий нулевой символ.

Требования к реализации: при выполнении данного задания вы можете определять любые вспомогательные функции, если они
вам нужны. Определять функцию main не нужно.
*/

#include <iostream>
using namespace std;

char *resize(const char *str, unsigned size, unsigned new_size) {
    char *new_str = new char[new_size];

    for (int i = 0; i < size && i < new_size; i++) {
        new_str[i] = str[i];
    }

    delete[] str;

    return new_str;
}

char *getline() {
    int const base_size = 10;
    int new_size;
    int size = base_size;
    int count = 0;
    char *str = new char[size];
    char c;

    while (cin.get(c) && c != '\n') {
        str[count] = c;
        count++;
        if (count == size) {
            new_size = size + base_size;
            str = resize(str, size, new_size);
            size = new_size;
        }
    }

    str[count] = '\0';

    return str;
}

int main() {
    char *s = getline();
    cout << "Your string: " << s << endl;
    cout << "String length: " << strlen(s) << endl;
    return 0;
}