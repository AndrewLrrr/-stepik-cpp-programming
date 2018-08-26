/*
В этой задаче вам требуется реализовать оператор [] для уже известного вам класса String. Однако на этот раз оператор
должен реализовывать нестандартное поведение: оператор нужно реализовать таким образом, чтобы для объекта str класса
String можно было писать str[i][j] и это выражение возвращало подстроку начинающуюся в позиции i (считая с 0) и
заканчивающуюся в позиции j (не включая).

Например:
String const hello("hello");
String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"

Обратите внимание, что i может равняться j, в этом случае результатом должна быть пустая строка. Гарантируется, что i
никогда не будет больше j, и они не будут выходить за пределы длины строки.
Требования к реализации: При выполнении задания вы можете создавать любые методы/конструкторы или даже
структуры/классы, если они вам нужны. Реализовывать методы, которые уже объявленны в шаблоне, не нужно  они уже
реализованы. При выполнении задания не вводите и не выводите что-либо. Реализовывать функцию main не нужно.
*/


#include <algorithm> // std::swap
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

    String & operator=(const String &other) {
        if (this != &other)
            String(other).swap(*this); // *this -> ссылка на текущий объект
        return *this;
    }

    void swap(String &s) {
        std::swap(size, s.size);
        std::swap(str, s.str);
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

    // New
    struct StringProxy {
        StringProxy(const char *str, size_t start_index, size_t size)
                : start_index_(start_index)
                , str_(new char[size - start_index + 1])
        {
            strcpy(this->str_, str + start_index);
        }

        ~StringProxy() {
            delete[] this->str_;
        }

        String operator[](int index) const {
            char *new_str = new char[index - this->start_index_ + 1];
            strncpy(new_str, this->str_, (index - this->start_index_));
            String s(new_str);
            delete[] new_str;
            return s;
        }

    private:
        size_t start_index_;
        char *str_;
    };

    // New
    StringProxy operator[](int index) const {
        return StringProxy(this->str, index, this->size);
    }

    // New
    operator char *() const {
        return this->str;
    }

    size_t size;
    char *str;
};

int main() {
    String const hello("hello");
    String const hell = hello[0][4];
    String const ell  = hello[1][4];
    String const empty1 = ell[0][0];
    String const empty2 = ell[1][1];
    String const empty3 = ell[2][2];

    cout << "hello = " << hello << endl;
    cout << "hello[0][4] = " << hello[0][4] << endl;
    cout << "ell[0][0] = " << empty1 << endl;
    cout << "ell[1][2] = " << empty2 << endl;
    cout << "ell[2][2] = " << empty3 << endl;

    return 0;
}
