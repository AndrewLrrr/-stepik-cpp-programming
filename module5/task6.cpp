/*
Помните иерархию Expression, которую мы разрабатывали на четвёртой неделе? Реализуйте ScopedPtr, который будет работать
с указателями на базовый класс Expression. В этом задании вам требуется реализовать методы get, release и reset,
операторы * и -> так, как это было описано в предыдущем степе. А также реализуйте конструктор ScopedPtr от указателя на
Expression.

Подсказка: в качестве признака того, что ScopedPtr не хранит никакого указателя (после вызова release), используйте
нулевой указатель, при этом вы можете явно проверить указатель в деструкторе, но делать это не обязательно, так как
delete от нулевого указателя ничего не делает.

Требования к реализации: ваш код не должен вводить или вводить что-либо, реализовывать функцию main не нужно.
*/

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
        cout << "BinaryOperation destructor " << action_ << endl;
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


struct ScopedPtr
{
    // реализуйте следующие методы:
    //
    explicit ScopedPtr(Expression *ptr = 0)
            : ptr_(ptr)
    {}

    ~ScopedPtr() {
        delete ptr_;
    }

    Expression *get() const {
        return ptr_;
    }

    Expression *release() {
        Expression *ptr = ptr_;
        ptr_ = 0;
        return ptr;
    }

    void reset(Expression *ptr = 0) {
        delete ptr_;
        ptr_ = ptr;
    }

    Expression &operator*() const {
        return *ptr_;
    }

    Expression *operator->() const {
        return ptr_;
    }

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};


int main() {
    ScopedPtr mul(new BinaryOperation(new Number(4.5), '*', new Number(5)));
    ScopedPtr add(new BinaryOperation(new Number(10), '+', new Number(5)));
    ScopedPtr sub(new BinaryOperation(new Number(10), '-', new Number(4)));
    ScopedPtr div(new BinaryOperation(new Number(9), '/', new Number(2)));
    ScopedPtr mul2(new BinaryOperation(new Number(9), '*', new Number(2)));

    Expression *add2 = add.release();
    Expression *div2 = div.get();
    mul2.reset(new BinaryOperation(new Number(2), '*', new Number(2)));

    cout << "4.5 * 5 = " << mul->evaluate() << endl;
    cout << "10 + 5 = " << add2->evaluate() << endl;
    cout << "10 - 4 = " << sub->evaluate() << endl;
    cout << "9 / 2 = " << div2->evaluate() << endl;
    cout << "2 * 2 = " << mul2->evaluate() << endl;
}