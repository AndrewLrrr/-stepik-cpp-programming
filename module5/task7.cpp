/*
Задание повышенной сложности.

Реализуйте класс SharedPtr как описано ранее. Задание немного сложнее, чем кажется на первый взгляд. Уделите особое
внимание "граничным случаям" — нулевой указатель, присваивание самому себе, вызов reset на нулевом SharedPtr и прочее.

Подсказка: возможно, вам понадобится завести вспомогательную структуру.

Требования к реализации: ваш код не должен вводить или вводить что-либо, реализовывать функцию main не нужно.
*/

#include <assert.h>
#include <cstddef>    // NULL
#include <algorithm>  // std::swap
#include <iostream>
using namespace std;


struct Expression {
    virtual ~Expression() {};

    virtual double evaluate() const = 0;
};


struct Number : Expression {
    explicit Number(double value)
            : Expression()
    {
        this->value_ = value;
    }

    double evaluate() const {
        return value_;
    };

private:
    double value_;
};


struct BinaryOperation : Expression {
    explicit BinaryOperation(Expression const *a, char action, Expression const *b)
            : Expression()
    {
        this->a_ = a;
        this->b_ = b;
        this->action_ = action;
    }

    ~BinaryOperation() {
        delete a_;
        delete b_;
    };

    double evaluate() const {
        double value = 0;

        switch (action_) {
            case '*':
                value = a_->evaluate() * b_->evaluate();
                break;
            case '+':
                value = a_->evaluate() + b_->evaluate();
                break;
            case '/':
                value = a_->evaluate() / b_->evaluate();
                break;
            case '-':
                value = a_->evaluate() - b_->evaluate();
                break;
        }
        return value;
    }

private:
    char action_;
    Expression const *a_;
    Expression const *b_;
};

// Tnx https://github.com/SRombauts/shared_ptr
//
struct SharedPtrCount {
    SharedPtrCount()
            : pn_(NULL)
    {}

    SharedPtrCount(const SharedPtrCount &count)
            : pn_(count.pn_)
    {}

    void swap(SharedPtrCount &lhs) {
        std::swap(pn_, lhs.pn_);
    }

    long use_count() const {
        if (pn_ != NULL) {
            return  *pn_;
        }
        return 0;
    }

    void acquire(Expression *ptr) {
        if (ptr != NULL) {
            if (pn_ == NULL) {
                try {
                    pn_ = new long(1); // may throw std::bad_alloc
                }
                catch (std::bad_alloc &) {
                    delete ptr;
                    throw; // rethrow the std::bad_alloc
                }
            }
            else {
                ++(*pn_);
            }
        }
    }

    void release(Expression *ptr) {
        if (pn_ != NULL) {
            --(*pn_);
            if (*pn_ == 0) {
                delete ptr;
                delete pn_;
            }
            pn_ = NULL;
        }
    }

private:
    long *pn_;
};

struct SharedPtr
{
    // реализуйте следующие методы
    //
    explicit SharedPtr(Expression *ptr = 0)
            : pn_()
    {
        acquire(ptr);
    }

    SharedPtr(const SharedPtr &ptr)
            : pn_(ptr.pn_)
    {
        assert((ptr.px_ == NULL) || (ptr.use_count() != 0));
        acquire(ptr.px_);
    }

    SharedPtr &operator=(const SharedPtr &ptr) {
        swap(ptr);
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    Expression *get() const {
        return px_;
    }

    void reset(Expression *ptr = 0) {
        assert((ptr == NULL) || (ptr != px_));
        release();
        acquire(ptr);
    }

    long use_count() const {
        return pn_.use_count();
    }

    Expression &operator*() const {
        assert(px_ != NULL);
        return *px_;
    }

    Expression *operator->() const {
        return px_;
    }

private:
    void acquire(Expression *ptr) {
        pn_.acquire(ptr);
        px_ = ptr;
    }

    void release() {
        pn_.release(px_);
        px_ = NULL;
    }

    void swap(SharedPtr lhs) {
        std::swap(px_, lhs.px_);
        pn_.swap(lhs.pn_);
    }

    Expression    *px_; // Native pointer
    SharedPtrCount pn_; // Reference counter
};


int main() {
    SharedPtr mul(new BinaryOperation(new Number(4.5), '*', new Number(5)));
    SharedPtr add(new BinaryOperation(new Number(10), '+', new Number(5)));
    SharedPtr sub(new BinaryOperation(new Number(10), '-', new Number(4)));

    SharedPtr add2 = add;
    SharedPtr add3 = add;
    SharedPtr add4 = add;
    SharedPtr sub2 = sub;
    cout << "add use_count = " << add.use_count() << endl;
    cout << "sub use_count = " << sub.use_count() << endl;
    cout << "mul use_count = " << mul.use_count() << endl;

    cout << "4.5 * 5 = " << mul->evaluate() << endl;
    cout << "10 + 5 = " << add->evaluate() << endl;
    //cout << "10 + 5 = " << add2->evaluate() << endl;
    cout << "10 - 4 = " << sub->evaluate() << endl;
    //cout << "10 - 4 = " << sub2->evaluate() << endl;

    add2 = mul;
    cout << "add use_count = " << add.use_count() << endl;
    cout << "mul use_count = " << mul.use_count() << endl;
    cout << "4.5 * 5 = " << mul->evaluate() << endl;
    //cout << "4.5 * 5 = " << add2->evaluate() << endl;

    add3 = sub;
    cout << "add use_count = " << add.use_count() << endl;
    cout << "sub use_count = " << sub.use_count() << endl;
    cout << "10 - 4 = " << sub->evaluate() << endl;
    //cout << "10 - 4 = " << add3->evaluate() << endl;
}