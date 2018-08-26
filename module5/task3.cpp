/*
Еще одна важная группа операторов, которые полезно реализовать для класса рациональных чисел — это операторы сравнения.
Реализуйте операторы <, <=, >, >=, ==, != для класса Rational так, чтобы можно было сравнивать объекты класса Rational
не только друг с другом, но и с целыми числами.

При решении задания не используйте метод to_double, он введен в класс, в первую очередь, для удобства тестирования. Вы
можете определять любые вспомогательные методы или функции если необходимо.

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
    Rational number3(150, 30);
    Rational number4(3, 1);

    // 5 < 10 = 1
    cout << "5 < 10 = " << (number1 < 10) << endl;

    // -10 < 0 = 1
    cout << "-10 < 0 = " << (-10 < number0) << endl;

    // -10 > 0 = 0
    cout << "-10 > 0 = " << (-10 > number0) << endl;

    // -5 < -3 = 1
    cout << "-5 < -3 = " << (-number1 < -number2) << endl;

    // 5 < 5 = 0
    cout << "5 < 5 = " << (number1 < number3) << endl;

    // 5 <= 5 = 1
    cout << "5 <= 5 = " << (number1 <= number3) << endl;

    // 5 > 5 = 0
    cout << "5 > 5 = " << (number1 > number3) << endl;

    // 5 >= 5 = 1
    cout << "5 >= 5 = " << (number1 >= number3) << endl;

    // 5 == 5 = 1
    cout << "5 == 5 = " << (number1 == number3) << endl;

    // 5 != 3 = 0
    cout << "5 != 3 = " << (number1 == number2) << endl;

    // 3 == 3 = 1
    cout << "3 == 3 = " << (number2 == number4) << endl;

    // 5 > 3 = 1
    cout << "5 > 3 = " << (number1 > number2) << endl;

    // 5 < 3 = 0
    cout << "5 < 3 = " << (number1 < number2) << endl;

    // 5 >= 4 = 1
    cout << "5 >= 4 = " << (number1 >= 4) << endl;

    // 4 <= 5 = 1
    cout << "4 <= 5 = " << (4 <= number1) << endl;

//    for (int i = -100; i <= 100; ++i) {
//        for (int j = 1; j <= 100; ++j) {
//            Rational r1 = Rational(i, j);
//            double s1 = (double) i / (double) j;
//            for (int k = -100; k <= 100; ++k) {
//                for (int m = 1; m <= 100; ++m) {
//                    Rational r2 = Rational(k, m);
//                    double s2 = (double) k / (double) m;
//                    if ((r1 < r2) != (s1 < s2)) {
//                        cout << "Error: " << i << "/" << j << " < " << k << "/" << m << " != ";
//                        cout << s1 << " < " << s2 << endl;
//                    }
//                }
//            }
//        }
//    }

    return 0;
}