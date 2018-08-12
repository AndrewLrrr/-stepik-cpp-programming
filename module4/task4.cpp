/*
На прошлом степе вы познакомились с реализацией паттерна посетитель. Теперь пришло время воспользоваться этими
знаниями. Ваш класс должен печатать (используя std::cout) текстовое представление арифметического выражения. Т.е. для
объекта класса Number он должен напечатать число, которое в нем хранится, а для объекта класса BinaryOperation он
должен напечатать левый операнд, затем операцию, а затем правый операнд.

Учтите, что операции + и - имеют меньший приоритет, чем операции * и /, т. е. возможно вам придется печатать
дополнительные круглые скобки, чтобы сохранить правильный порядок операций.

Классы иерархии Expression и абстрактный класс Visitor приведены в комментарии в шаблоне для удобства.

При проверке задания лишние пробелы или лишние скобки будут игнорироваться, т.е. вывод "1+2" эквивалентен выводу
"( ( 1 )  +   ( 2 ) )", а вот вывод "1 + 2 * 3" не эквивалентен выводу "((1 + 2) * 3)". Вы можете попытаться
минимизировать количество скобок в выводе, но это не требуется.

Перед выполнением задания внимательно прочитайте содержимое предыдущего степа.

Требования к реализации: при выполнении задания вы можете заводить любые вспомогательные классы или функции, но не
нужно реализовывать функцию main или менять реализацию классов иерархии Expression.
*/

#include <iostream>


struct Number;
struct BinaryOperation;


struct Visitor {
    virtual void visitNumber(Number const *number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const *operation) = 0;
    virtual ~Visitor() {};
};


struct Expression {
    virtual double evaluate() const = 0;
    virtual void visit(Visitor *visitor) const = 0;
    virtual ~Expression() {};
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

    double get_value() const {
        return value_;
    }

    void visit(Visitor *visitor) const {
        visitor->visitNumber(this);
    }

private:
    double value_;
};


struct BinaryOperation : Expression {
    explicit BinaryOperation(Expression const *left, char op, Expression const *right)
            : Expression()
    {
        this->left_ = left;
        this->right_ = right;
        this->op_ = op;
    }

    ~BinaryOperation() {
        delete left_;
        delete right_;
    };

    double evaluate() const {
        double value = 0;

        switch (op_) {
            case '*':
                value = left_->evaluate() * right_->evaluate();
                break;
            case '+':
                value = left_->evaluate() + right_->evaluate();
                break;
            case '/':
                value = left_->evaluate() / right_->evaluate();
                break;
            case '-':
                value = left_->evaluate() - right_->evaluate();
                break;
        }
        return value;
    }

    Expression const *get_left() const {
        return left_;
    }

    Expression const *get_right() const {
        return right_;
    }

    char get_op() const {
        return op_;
    }

    void visit(Visitor *visitor) const {
        visitor->visitBinaryOperation(this);
    }

private:
    char op_;
    Expression const *left_;
    Expression const *right_;
};


/* Этот класс вам нужно реализовать */
struct PrintVisitor : Visitor {
    void visitNumber(Number const *number) {
        std::cout << number->get_value();
    }

    void visitBinaryOperation(BinaryOperation const *operation) {
        std::cout << "(";
        operation->get_left()->visit(this);
        std::cout << " " << operation->get_op() << " ";
        operation->get_right()->visit(this);
        std::cout << ")";
    }
};


int main() {
    PrintVisitor visitor;

    // 3 + (1 + 1.5) * 5 = 15.5
    Expression *a = new BinaryOperation(new Number(1), '+', new Number(1.5));
    Expression *b = new BinaryOperation(a, '*', new Number(5));
    Expression *c = new BinaryOperation(new Number(3), '+', b);
    std::cout << "Expression: ";
    c->visit(&visitor);
    std::cout << " = " << c->evaluate() << std::endl;
    delete c;

    // ((10 - 2) / (6.5 + 1.5) + 1) * 5 = 10
    Expression *d = new BinaryOperation(new Number(10), '-', new Number(2));
    Expression *e = new BinaryOperation(new Number(6.5), '+', new Number(1.5));
    Expression *g = new BinaryOperation(d, '/', e);
    Expression *f = new BinaryOperation(g, '+', new Number(1));
    Expression *h = new BinaryOperation(f, '*', new Number(5));
    std::cout << "Expression: ";
    h->visit(&visitor);
    std::cout << " = " << h->evaluate() << std::endl;
    delete h;


    return 0;
}