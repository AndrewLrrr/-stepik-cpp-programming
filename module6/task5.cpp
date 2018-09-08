/*
Реализуйте шаблонную функцию minimum, которая находит минимальный элемент, который хранится в экземпляре шаблонного
класса Array, при этом типовой параметр шаблона Array может быть произвольным. Чтобы сравнивать объекты произвольного
типа, на вход функции также будет передаваться компаратор, в качестве компаратора может выступать функция или объект
класса с перегруженным оператором "()". Примеры вызова функции minimum:

bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };
Array<int> ints(3);
ints[0] = 10;
ints[1] = 2;
ints[2] = 15;
int min = minimum(ints, less); // в min должно попасть число 2
int max = minimum(ints, Greater()); // в max должно попасть число 15
*/

#include <iostream>
#include <cstddef>

bool less(int a, int b) { return a < b; }

struct Greater { bool operator()(int a, int b) const { return b < a; } };

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

template <typename Type, typename Comp>
Type minimum(Array<Type> &ar, Comp f) {
    Type m = ar[0];
    for (size_t i = 1; i < ar.size(); ++i) {
        if (f(ar[i], m)) {
            m = ar[i];
        }
    }
    return m;
}

int main() {
    int ints[] = {2, 5, 3, 42, 1, 10};
    Array<int> a(size_t(6), 0);

    for (size_t i = 0; i < 6; ++i) {
        a[i] = ints[i];
    }

    std::cout << "min less = " << minimum<int>(a, less) << std::endl;

    Greater greater;
    std::cout << "min Greater = " << minimum<int>(a, greater) << std::endl;
}