// stack memory vs heap memory
// value semantics vs reference semantics

// global scope, local scope
// free-functions

// class/struct? object? ------> type? instance?
// typedef (C)

// c-tor of a primitive type
// c-tor of a complex type (struct)

// write a c-tor of a struct instance as a free function (imperative programming paradigm)
// write a c-tor of a struct instance as a member function (OOP paradigm)

// allocate memory at run-time (dynamic memory allocation)
// free memory at run-time

// write a dtor as a free function (imperative programming paradigm)
// write a dtor as a member function (OOP paradigm)

// member variables ~= attributes ~= properties (OOP)

#include <iostream>

using namespace std;

int i = 10;

struct Vector2d {
    int a;
    int b;

    Vector2d() : a(0), b(0) { }
    Vector2d(int a_, int b_) : a(a_), b(b_) { }


    // Modern C++ optimizes away unnecessary copies or moves when returning objects, making return-by-value efficient through mechanisms
    // like RVO (Return Value Optimization).
    Vector2d addVectors(const Vector2d& second) {
        Vector2d result; // default c-tor

        result.a = this->a + second.a;
        result.b = this->b + second.b;

        return result;
    }

    Vector2d operator+(const Vector2d& right) {
        Vector2d result;

        result.a = this->a + right.a;
        result.b = this->b + right.b;

        return result;
    }

};

void func() {
    // first 2d vector instance
    Vector2d A(5, 7);
    cout << "Vector A: [" << A.a << ", " << A.b <<  "]" << endl;

    // Second 2d vector instance
    Vector2d B(-1, 3);
    cout << "Vector B: [" << B.a << ", " << B.b <<  "]" << endl;

    Vector2d C = A + B;
    cout << "Results of A + B: [" << C.a << ", " << C.b <<  "]" << endl;

    Vector2d D = A.addVectors(B);
    cout << "Results A + B: [" << D.a << ", " << D.b <<  "]" << endl;

}

int main()
{
    func();
    return 0;
}
