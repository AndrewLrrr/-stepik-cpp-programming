#include <iostream>
using namespace std;


struct A {
    virtual int bar() = 0;

protected:
    void print() {
        cout << "print from A" << endl;
    }

private:
    virtual int foo() = 0;
    void privatePrint() {
        cout << "private print from A" << endl;
    }
};


struct B : A {
    int foo() {
        return 5;
    }

    void printBar() {
        cout << "print bar from B = " << this->bar() << endl;
    }

//    Error:
//    void printPrivatePrint() {
//        this->privatePrint();
//    }

private:
    int bar() {
        return 10;
    }
};


struct C : private A {
    int bar() {
        return 20;
    }

    void printPrint() {
        this->print();
    }

    void printFoo() {
        cout << "print foo from C = " << this->foo() << endl;
    }

private:
    int foo() {
        return 15;
    }
};


int main() {
    B *b = new B();
    cout << b->foo() << endl;
    b->printBar();
    // cout << b->bar() << endl; Error

    C *c = new C();
    c->printFoo();
    c->printPrint();
}