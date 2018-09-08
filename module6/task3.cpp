/*
Шаблонные классы можно наследовать. Реализуйте шаблонную структуру ValueHolder с одним типовым параметром T,
унаследованную от интерфейса ICloneable. Интерфейс ICloneable содержит всего один виртуальный метод ICloneable* clone()
const, который должен вернуть указатель на копию объекта, на котором он был вызван (объект должен быть создан в куче).
Шаблон ValueHolder, как говорит его название, хранит всего одно значение (назовите его data_) типа T (для типа T
определен конструктор копирования). Не делайте поле data_ закрытым (поэтому в данном случае мы явно пишем, что
ValueHolder должна быть структурой).
*/

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

#include <iostream>
using namespace std;


struct ICloneable
{
    virtual ICloneable *clone() const = 0;
    virtual ~ICloneable() {}
};


template <typename T>
struct ValueHolder : ICloneable
{
    ValueHolder(const T &t) : data_(t)
    {}

    ValueHolder<T> *clone() const {
        return new ValueHolder<T>(this->data_);
    }

    T data_;
};


int main() {
    int a = 5;
    cout << "a = " << a << endl;

    ValueHolder<int> va(a);
    cout << "va.data_ = " << va.data_ << endl;

    ValueHolder<int> *vb = va.clone();
    cout << "vb->data_ = " << vb->data_ << endl;
}
