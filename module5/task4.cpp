/*
Добавьте в класс Rational оператор приведения к double. Все операторы из предыдущих заданий отсутствуют и реализовывать
их не нужно. Метод to_double можно использовать в этом задании.

Важное замечание: добавлять оператор преобразования к double в класс Rational не самая удачная идея, например, потому,
что при таком преобразовании может происходить потеря точности. Эта задача дана исключительно с целью ознакомления с
правильным порядком перегрузки таких операторов.

Требования к реализации: ваш код не должен вводить или вводить что-либо, реализовывать функцию main не нужно.
*/

#include <iostream>
using namespace std;


int CD(int a, int b) {
    int i = a;
    int j = b;
    int c = 1;

    while (i != j) {
        ++c;
        if (i < j)
            i += a;
        else
            j += b;
    }

    return j;
}


struct Rational
{
    Rational(int numerator = 0, int denominator = 1)
            : numerator_(numerator)
            , denominator_(denominator)
    {}

    void add(Rational rational) {
        int cd = CD(denominator_, rational.get_denominator());
        numerator_ = numerator_ * (cd / denominator_) + rational.get_numerator() * (cd / rational.get_denominator());
        denominator_ = cd;
    }

    void sub(Rational rational) {
        int cd = CD(denominator_, rational.get_denominator());
        numerator_ = numerator_ * (cd / denominator_) - rational.get_numerator() * (cd / rational.get_denominator());
        denominator_ = cd;
    }

    void mul(Rational rational) {
        numerator_ *= rational.get_numerator();
        denominator_ *= rational.get_denominator();
    }

    void div(Rational rational) {
        numerator_ *= rational.get_denominator();
        denominator_ *= rational.get_numerator();
    }

    void neg() {
        numerator_ *= -1;
    }

    void inv() {}

    double to_double() const {
        return (double) numerator_ / (double) denominator_;
    }

    int get_numerator() const {
        return numerator_;
    }

    int get_denominator() const {
        return denominator_;
    }

    Rational &operator+=(Rational const &rational) {
        this->add(rational);
        return *this;
    }

    Rational &operator-=(Rational const &rational) {
        this->sub(rational);
        return *this;
    }

    Rational &operator*=(Rational const &rational) {
        this->mul(rational);
        return *this;
    }

    Rational &operator/=(Rational const &rational) {
        this->div(rational);
        return *this;
    }

    Rational operator+() const {
        return Rational(numerator_, denominator_);
    }

    Rational operator-() const {
        return Rational(numerator_ * -1, denominator_);
    }

    operator double() const {
        return this->to_double();
    }

private:
    int numerator_;
    int denominator_;
};

Rational operator+(Rational r, Rational const &rational) {
    r.add(rational);
    return r;
}

Rational operator-(Rational r, Rational const &rational) {
    r.sub(rational);
    return r;
}

Rational operator*(Rational r, Rational const &rational) {
    r.mul(rational);
    return r;
}

Rational operator/(Rational r, Rational const &rational) {
    r.div(rational);
    return r;
}

bool operator==(Rational const &a, Rational const &b) {
    Rational c = a - b;
    return c.get_numerator() == 0;
}

bool operator!=(Rational const &a, Rational const &b) {
    return !(a == b);
}

bool operator<(Rational const &a, Rational const &b) {
    Rational c = a - b;
    if (b.get_numerator() >= 0 && a.get_numerator() < 0)
        return true;
    else if (b.get_numerator() < 0 && a.get_numerator() >= 0)
        return false;
    else
        return c.get_numerator() < 0;
}

bool operator>(Rational const &a, Rational const &b) {
    return b < a;
}

bool operator<=(Rational const &a, Rational const &b) {
    return !(b < a);
}

bool operator>=(Rational const &a, Rational const &b) {
    return !(b > a);
}


int main() {
    Rational number0(0);
    Rational number1(10, 2);
    Rational number2(12, 4);
    Rational number3(14, 4);

    double n0 = (double) number0;
    double n1 = (double) number1;
    double n2 = (double) number2;
    double n3 = (double) number3;

    cout << "0 = " << n0 << endl;
    cout << "5 = " << n1 << endl;
    cout << "3 = " << n2 << endl;
    cout << "3.5 = " << n3 << endl;

    return 0;
}