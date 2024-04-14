#include <iostream>

// function objects
// function pointers

// repeat-it algorithm
// mutability
// l-value, r-value, r-value binding reference

// move-ctor, move-assignment

using namespace std;

//typedef void (*foo_ptr)(); // C notation
using dummyfunc_ptr = void (*)(); // C++ Notation

void foo() { cout << "I am a dummy function" << endl; }
void bar() { cout << "I am a dummy function too" << endl; }

using one_inter_ptr = int(*)(int);

int foo(int i) { return i+1; }
int bar(int j) { return j-1; }
int xyz(int i) { return i*2; }

void process(int a, one_inter_ptr p) {
    cout << p(a) << endl;
}

using two_inter_ptr = int (*)(int, int);
int foo(int a, int b) { return a + b; }

void process(int a, int b, two_inter_ptr p) {
    cout << p(a,b) << endl;
}

struct FunctionObject {
    int a;
    int b;

    int operator() (int c) {
        return a + b + c;
    }
};

void process(FunctionObject fo, int k) {
    cout << fo(k) << endl;
}


template<typename T>
void repeat_it(T fo, int num_times) {
    for (int i = 0; i < num_times; i++)
        cout << fo() << endl;
}


struct FibonacciGenerator {
    int a = 0;
    int b = 1;

    int operator() () {
        auto retval = a + b;
        a = b;
        b = retval;

        return retval;
    }
};


int main(int argc, char* argv[])
{

    // function overloaded
//    auto a = &foo;
//    cout << a << endl;

    // Direct Calls
    foo();
    bar();

    // Indirect calls
    dummyfunc_ptr p = &foo;
    cout << p << endl;
    p();

    p = &bar;
    p();

    process(5, &foo);
    process(5, &bar);
    process(5, &xyz);

    process(5, 10, &foo);

    FunctionObject fo{10, 25}; // unified/universal ctor syntax
    process(fo, 3);
//    repeat_it(fo, 3);

//    repeat_it<FunctionObject>(fo, 3); // you can manually deduce the type

    repeat_it(FibonacciGenerator{}, 10);

    // Using lambda
    repeat_it([a=0, b=1]() mutable {
        auto retval = a + b;
        a = b;
        b = retval;
        return retval;
    }, 10);
}
