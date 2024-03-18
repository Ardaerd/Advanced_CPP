// Fraction class: Want to represent rational numbers with a numerator and denominator

// OOP: (encapsulates all necessary tools in a box that communicates
//  with caller via c-tors, assignment operators, and casting
// ctor/dtor
// copy-ctor, copy-assignment
// casting
// inheritance (will discuss later)

// function overloading, overload set
// operators and operator overloading

// literals, types of constants (remember units in your Physics class: 9.8 m/s^2)
// user-defined literals (a special way to create your own literals)

// Celsius/Fahrenheit example
// converting constructors

// pass by value, pass by reference, pass by constant reference
// implicit/explicit constructors

// operator== and operator+ overloads for Celsius/Fahrenheit
// static attributes and staticness. static variable initialization

#include <iostream>
#include <vector>

using namespace std;

struct Fraction {
    int n;
    int d;

    Fraction(int n, int d = 1) : n(n), d(d) { }

    // Copy Construction overloading
    Fraction(const Fraction& other) : n(other.n), d(other.d) {
        cout << "copy constructor of Fraction called" << endl;
    }

    // overloading the "=" operation
    void operator=(const Fraction& right) { // Copy assignment operator
        this->n = right.n;
        this->d = right.d;

        cout << "Copy assignment of Fraction called" << endl;
    }

    operator double() {
        return double(n)/d;
    }
};


auto operator"" _frac(long double value) {
    return Fraction(int(value));
}


void print(const Fraction& f) {
    cout << f.n << "/" << f.d << endl;
}


int main()
{
    auto f1 = Fraction(1, 4);
    auto f2 = Fraction(5);

    f1 = f2; // copy assignment // you can use move too
    // f1.operator=(f2) // behind the scene operation
    print(f1);

    f1 = 15; // automatic encapsulation // if you don't want use excplicit keyword rigt before const
    print(f1);

    Fraction f3(f1); // Copy Construction
    Fraction f4 = f1; // copy Construction
    auto f5 = f1; // copy Construction

    f5 = f1; // copy assignment

    cout << Fraction(15, 4) << endl;
    cout << 25.5_frac << endl;
    return 0;
}
