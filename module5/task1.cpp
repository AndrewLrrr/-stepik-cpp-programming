/*
Вам дан класс Rational, который описывает рациональное число. В нем определены методы add, sub, mul и div, которые
прибавляют к нему число, отнимают число, умножают на число и делят на число соответственно. Кроме того в нем определен
метод neg, который меняет знак на противоположный.

Вам нужно определить операторы +=, -=, *=, /= для класса Rational так, чтобы они могли принимать в качестве аргументов
и объекты типа Rational и целые числа. Кроме того вам необходимо определить операторы унарного минуса и плюса для
класса Rational.

Требования к реализации: ваш код не должен вводить или вводить что-либо, реализовывать функцию main не нужно. Кроме
того, нельзя (это совершенно не нужно) использовать динамическую память или подключать какие-либо библиотеки.
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


int main() {
    Rational number1(10, 2);
    Rational number2(12, 4);
    Rational number3(5, 2);

    // 5 - 3 = 2
    number1 -= number2;
    cout << "5 - 3 = " << number1.to_double() << endl;

    // 2 * 4 = 8
    number1 *= 4;
    cout << "2 * 4 = " << number1.to_double() << endl;

    // 8 = -8
    number1 = -number1;
    cout << "8 = " << number1.to_double() << endl;

    // -8 = +(-8) = -8
    number1 = +number1;
    cout << "8 = +(-8) = " << number1.to_double() << endl;

    // -8 * -2 = 16
    number1 *= -2;
    cout << "-8 * -2 = " << number1.to_double() << endl;

    // 16 / 2.5 = 6.4
    number1 /= number3;
    cout << "16 / 2.5 = " << number1.to_double() << endl;

    cout << "(-number1).to_double() = " << (-number1).to_double() << endl;

    return 0;
}