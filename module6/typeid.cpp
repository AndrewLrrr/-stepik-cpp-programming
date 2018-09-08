#include <iostream>
using namespace std;

template <typename T>
void WhatEver(void)
{
    T t;
    // How to print with cout the T value (not the t value)?
    cout << typeid(t).name() << endl;
}

struct ICloneable {
    virtual ICloneable *clone() const = 0;
    virtual ~ICloneable() {}
};

template <typename T>
struct ValueHolder : ICloneable {
    ValueHolder(const T &t) {
        this->data_ = new T(t);
    }

    ~ValueHolder() {
        delete this->data_;
    }

    ValueHolder<T> *clone() const {
        cout << "ValueHolder<T> *clone()" << endl;
        return new ValueHolder<T>(*this->data_);
    }

    T *data_;
};

int main()
{
    WhatEver<int>();
    WhatEver<double>();
    cout << typeid(WhatEver<double>()).name() << endl;
    ValueHolder<int> i(10);
    ValueHolder<char> c('a');
    cout << typeid(i).name() << endl;
    cout << typeid(c).name() << endl;
}