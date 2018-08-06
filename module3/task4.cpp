/*
Определен следующий класс (он также приведен в комментарии в шаблоне кода):

struct Cls {
    Cls(char c, double d, int i);
private:
    char c;
    double d;
    int i;
};

Как видно, все поля этого класса закрытые, ваша задача реализовать несколько функций, которые дают полный доступ к этим
полям (см. шаблон кода), несмотря на то, что они закрытые.

Внимание: предполагаемое решение этого задания существенно опирается на Undefined Behaviour и является исключительно
учебным, но полезно для лучшего понимания того, как работают модификаторы доступа. Решение было проверено на различных
компиляторах (g++/clang++/icc/msvc), но мы настоятельно не рекомендуем использовать подобные трюки в боевом коде.

Требования к реализации: при решении этого задания вам разрешается заводить любые вспомогательные функции и классы, но
не изменять определение класса Cls. Не нужно вводить или выводить что-либо, также не нужно определять функцию main.
*/

#include <iostream>
using namespace std;

// sizeof(char) = 1 байт
// sizeof(double) = 8 байт
// sizeof(int) = 4 байта
// sizeof(cls) = 24 байта
// Расположение структуры в памяти после выравнивания:
// cls = [c * * * * * * * d d d d d d d d i i i i * * * *]
// d - выравнивается на позицию кратную 8 и вся структура приводится к размеру кратному 8 (см. memory_align.c)
struct Cls {
    Cls(char c, double d, int i)
        : c(c)
        , d(d)
        , i(i)
    {}

    private:
        char c;
        double d;
        int i;
};

// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    // Указатель на первый элемент в памяти
    //  |
    // [c * * * * * * * d d d d d d d d i i i i * * * *]
    return * (char *) &cls;
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    // Указатель на второй элемент в памяти
    //                  |
    // [c * * * * * * * d d d d d d d d i i i i * * * *]
    // Приводим указатель к единице, чтобы смещение составляло 1 байт
    char *p = (char *) &cls;
    return * (double *) (p + 8);
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
    // Указатель на третий элемент в памяти
    //                                  |
    // [c * * * * * * * d d d d d d d d i i i i * * * *]
    // Приводим указатель к единице, чтобы смещение составляло 1 байт
    char *p = (char *) &cls;
    return * (int *) (p + 16);
}

int main() {
    cout << "sizeof(char) = " << sizeof(char) << endl;
    cout << "sizeof(double) = " << sizeof(double) << endl;
    cout << "sizeof(int) = " << sizeof(int) << endl;
    cout << "sizeof(cls) = " << sizeof(struct Cls) << endl;
    Cls cls = Cls('a', 1.5, 15);
    cout << "c = " << get_c(cls) << endl;
    cout << "d = " << get_d(cls) << endl;
    cout << "i = " << get_i(cls) << endl;
    return 0;
}