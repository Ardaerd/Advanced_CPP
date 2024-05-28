// godbolt.org website
// factorial: consexpr function, meta programming version, meta programming with integr

#include <type_traits>
#include <iostream>

using namespace std;

// this code initialized in the run time
//int factorial(int n) {
//    if(n == 0) return 1;
//    return n * factorial(n-1);
//}

// now we are saying if it can be compile time make it in compile time
//constexpr int factorial(int n) {
//    if (n == 0) return 1;
//    return n * factorial(n-1);
//}

// Now we are forcing compiler to make this operation in compile time
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

int main()
{
//    constexpr int a = factorial(5);

    constexpr int a = Factorial<5>::value;
    cout << a << endl;
    return a;
    // return Factorial<5>::value;
}
