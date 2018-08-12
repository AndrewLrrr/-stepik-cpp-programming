/*
(Задание повышенной сложности) Предполагаемое решение этого задания не переносимо с точки зрения стандарта, однако оно
проверено на различных версиях компиляторов g++/clang++/msvc. Решение этого задания не обязательно для получения
диплома по этому курсу, однако мы считаем его полезным, чтобы лучше понять как устроены виртуальные функции внутри.

Вам требуется реализовать функцию, которая принимает на вход два указателя на базовый класс Expression, и возвращает
true, если оба указателя указывают на самом деле на объекты одного и того же класса, и false в противном случае (т.е.
если оба указателя указывают на BinaryOperation, то возвращается true, а если один из них указывает на Number, а второй
на BinaryOperation, то false).

Требования к реализации: пользоваться typeid и dynamic_cast запрещено. Вызывать методы по переданным указателям
запрещено.
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


/*
Number *object1 = new Number(2);
|
|                                  object1            The virtual table
|                              _______________           _________
|-- [ Number pointer ] -----> [ vfptr pointer ] ------> [ pointer ] ----> (Some virtual method 1)
                              [ ............. ]      |  [ pointer ] ----> (Some virtual method 2)
                                                     |  [ ....... ]
Number *object2 = new Number(10);                    |
|                                                    |
|                                  object2           |
|                              _______________       |
|-- [ Number pointer ] -----> [ vfptr pointer ] ---> |
                              [ ............. ]

int *vptr = *(int**) object1; -> Получение доступа к адресу таблицы виртуальных методов и преобразование этого
указателя его к стандартному типу int (мог бы быть char или long)

long vptr = *(long*) object1; -> Получение значения адресу таблицы виртуальных методов
*/

bool check_equals(Expression const *left, Expression const *right) {
    long lvptr =  *(long*) left;
    long rvptr =  *(long*) right;

    return lvptr == rvptr;
}

int main() {
    bool correct1 = check_equals(
            new BinaryOperation(new Number(2.4), '+', new Number(1)),
            new BinaryOperation(new Number(20.4), '*', new Number(10))
    );
    cout << "Check BinaryOperation and BinaryOperation = " << correct1 << endl;

    bool correct2 = check_equals(new Number(2.4), new Number(20));
    cout << "Check Number and Number = " << correct2 << endl;

    bool incorrect1 = check_equals(new Number(2.4), new BinaryOperation(new Number(20.4), '*', new Number(10)));
    cout << "Check Number and BinaryOperation = " << incorrect1 << endl;

    bool incorrect2 = check_equals(new BinaryOperation(new Number(20.4), '*', new Number(10)), new Number(20));
    cout << "Check BinaryOperation and Number = " << incorrect2 << endl;

    return 0;
}