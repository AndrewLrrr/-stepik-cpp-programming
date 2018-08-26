/*
Определите для класса Rational операторы сложения, вычитания, умножения и деления, так чтобы объекты типа Rational
можно было складывать (вычитать, умножать и делить) не только друг с другом но и с целыми числами.

Требования к реализации: ваш код не должен вводить или выводить что-либо, реализовывать функцию main не нужно.
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


int main() {
    Rational number1(10, 2);
    Rational number2(12, 4);
    Rational number3(5, 2);

    // 5 - 3 = 2
    Rational number4 = number1 - number2;
    cout << "5 - 3 = " << number4.to_double() << endl;

    // 2 + 2 = 4
    Rational number5 = number4 + 2;
    cout << "2 + 2 = " << number5.to_double() << endl;

    // 4 * 2.5 = 10
    Rational number6 = number5 * number3;
    cout << "4 * 2.5 = " << number6.to_double() << endl;

    // 12 / 5 = 2.4
    Rational number7 = 12 / number1;
    cout << "12 / 5 = " << number7.to_double() << endl;

    // 2 + 2.4 = 4.4
    Rational number8 = 2 + number7;
    cout << "2 + 2.4 = " << number8.to_double() << endl;

    return 0;
}