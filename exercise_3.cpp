// function pointers
// for_each

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

int doit1(int a, int b) {return a;}
int doit2(int a, int b) {return a+b;}
int doit3(int a, int b) {return a-b;}

int dosmt1(int a) {return a;}
int dosmt2(int a) {return a*a;}
int dosmt3(int a) {return a+1;}

// Function pointer
using TwoInters = int (*)(int,int); // gets 2 int and output is one int
using OneInter = int (*)(int);

template<typename T>
void for_each(vector<T>& v, OneInter funcptr) {
    auto sz = v.size();

    for (decltype(sz) i = 0; i < sz; i++)
        v[i] = funcptr(v[i]);
}

template<typename T>
void print(const vector<T>& v) {
    for (const auto& item : v)
        cout << item <<endl;
}

int main()
{

    int choice = 2;
    int retval;

    TwoInters func;

    if (choice == 1)
        func = &doit1;
    else if (choice == 2)
        func = &doit2;
    else if (choice == 3)
        func = &doit3;

    retval = func(10,20);

    cout << retval << endl;

    if (choice == 1)
        retval = doit1(10,20);
    else if (choice == 2)
        retval = doit2(10,20);
    else if (choice == 3)
        retval = doit3(10,20);

    cout << retval << endl;

    cout << "Old fashion way: " << endl;
    vector<int> V(10);

    for (int i = 0; i<10; i++)
        V[i] = i;

    print(V);

    cout << "Advanced and Generic way: " << endl;

    for_each(V, &dosmt2);

    print(V);

    return 0;
}
