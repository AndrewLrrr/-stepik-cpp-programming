/*
Шаблонный класс Array может хранить объекты любого типа, для которого определён конструктор копирования, в том числе и
другой Array, например, Array< Array<int> >. Глубина вложенности может быть произвольной. Напишите шаблонную функцию
(или несколько) flatten, которая принимает на вход такой "многомерный" Array неизвестной заранее глубины вложенности и
выводит в поток out через пробел все элементы, хранящиеся на самом нижнем уровне. Примеры работы функции flatten:

Array<int> ints(2, 0);
ints[0] = 10;
ints[1] = 20;
flatten(ints, std::cout); // выводит на экран строку "10 20"
Array< Array<int> > array_of_ints(2, ints);
flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
Array<double> doubles(10, 0.0);
flatten(doubles, std::cout); // работать должно не только для типа int

Note: лидирующие и завершающие пробельные символы будут игнорироваться проверяющей системой, т. е. там где ожидается
"10 20" будет так же принят, например, вариант "   10 20   ", но не вывод "1020".

Hint: шаблонные функции тоже можно перегружать, из нескольких шаблонных функций будет выбрана наиболее специфичная.
*/


#include <iostream>

template <typename T>
class Array
{
public:
    explicit Array(size_t size, const T &value = T()) {
        this->size_ = size;
        this->data_ = static_cast<T*>(operator new[] (size * sizeof(T)));
        for (size_t i = 0; i < size; i++) {
            new (this->data_ + i) T(value);
        }
    }

    Array() {
        this->size_ = 0;
        this->data_ = nullptr;
    }

    Array(const Array &a) {
        this->size_ = a.size_;
        this->data_ = static_cast<T*>(operator new[] (a.size_ * sizeof(T)));
        for (size_t i = 0; i < a.size_; i++) {
            new (this->data_ + i) T(a.data_[i]);
        }
    }

    ~Array() {
        for (size_t i = 0; i < this->size_; i++) {
            this->data_[i].~T();
        }
        operator delete[] (this->data_);
    }

    Array &operator=(const Array &a) {
        if (this != &a)
            Array(a).swap(*this);
        return *this;
    }

    size_t size() const {
        return this->size_;
    }

    T &operator[](size_t i) {
        return this->data_[i];
    }

    const T &operator[](size_t i) const {
        return this->data_[i];
    }
private:
    void swap(Array &a) {
        std::swap(size_, a.size_);
        std::swap(data_, a.data_);
    }

    T *data_;
    size_t size_;
};


// Весь вывод должен осуществляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогательные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.

template <typename T>
void flatten(const T &item, std::ostream &out) {
    out << item << " ";
}

template <typename T>
void flatten(const Array<T> &array, std::ostream &out) {
    for (size_t i = 0; i < array.size(); ++i) {
        flatten(array[i], out);
    }
}

int main() {
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout); // выводит на экран строку "10 20"
    std::cout << std::endl;

    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
    std::cout << std::endl;

    Array<double> doubles(10, 0.0);
    doubles[0] = 10.5;
    doubles[2] = 20.2;
    flatten(doubles, std::cout); // работать должно не только для типа int
    std::cout << std::endl;

    return 0;
}