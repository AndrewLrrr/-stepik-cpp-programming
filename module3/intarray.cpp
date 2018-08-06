#include <iostream>
using namespace std;

struct IntArray {
    explicit IntArray(size_t size)
            : size_(size)
            , data_(new int[size])
    {
        for (size_t i = 0; i != size_; ++i)
            data_[i] = 0;
    }

    IntArray(IntArray const &a)
            : size_(a.size_)
            , data_(new int[size_])
    {
        for (size_t i = 0; i != size_; ++i)
            data_[i] = a.data_[i];
    }

    ~ IntArray () {
        delete [] data_;
    }

    IntArray &operator = (IntArray const &a) {
        if (this != &a)
            IntArray(a).swap(*this);
        return *this;
    }

    void swap(IntArray &a) {
        std::swap(size_, a.size_);
        std::swap(data_, a.data_);
    }

    size_t size() const { return size_; }

    int get(size_t i) const {
        return data_[i];
    }

    int &get(size_t i) {
        return data_[i];
    }

    void resize(size_t nsize) {
        IntArray t(nsize);
        size_t n = nsize > size_ ? size_ : nsize;
        for (size_t i = 0; i != n; ++i)
            t.data_[i] = data_[i];
        swap(t);
    }

private :
    size_t size_;
    int *data_;
};

int main() {
    int size = 10;
    IntArray a(size);

    for (int i = 0; i != size; ++i)
        a.get(i) = i;

    cout << "IntArray size = " << a.size() << endl;
    cout << "IntArray[2] = " << a.get(2) << endl;
    cout << endl;

    cout << "IntArray resize nsize = 20" << endl;
    cout << endl;

    a.resize(20);
    for (int i = size; i != 20; ++i)
        a.get(i) = i;

    cout << "IntArray size = " << a.size() << endl;
    cout << "IntArray[19] = " << a.get(19) << endl;
}