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
#include <list>


using namespace std;

int doit1(int a, int b) {return a;}
int doit2(int a, int b) {return a+b;}
int doit3(int a, int b) {return a-b;}

int dosmt1(int a) {return a;}
int dosmt2(int a) {return a*a;}
int dosmt3(int a) {return a+1;}

struct IncrementByKMulM {
    int K;
    int M;

    IncrementByKMulM(int K, int M) : K(K), M(M) { }

//    int run(int a) const {
//        return (a + K) * M;
//    }

    int operator() (int a) const {
        return (a+K)*M;
    }
};


// Function pointer
using TwoInters = int (*)(int,int); // gets 2 int and output is one int
using OneInter = int (*)(int);


//template<typename Container, typename Func>
//void transform(Container& v, Func funcptr) {

//    // More generic way
//    for (auto iter = v.begin(); iter != v.end(); iter++) {
//        auto& item = *iter;
//        item = funcptr(item);
//    }

////    auto sz = v.size();

////    for (decltype(sz) i = 0; i < sz; i++)
////        v[i] = funcptr(v[i]);

//}

template<typename Container, typename Object>
void transform(Container& v, const Object& obj) {

    // More generic way
    for (auto iter = v.begin(); iter != v.end(); iter++) {
        auto& item = *iter;
        item = obj(item);
    }

//    auto sz = v.size();

//    for (decltype(sz) i = 0; i < sz; i++)
//        v[i] = funcptr(v[i]);

}

template<typename Container>
void print(const Container& v) {

    // More Generic Way
    for (auto iter = v.begin(); iter != v.end(); iter++) {
        const auto& item = *iter;
        cout << item << ", " ;
    }
    cout << endl;

//    auto sz = v.size(); // unsigned int -> size_t

//    for (auto i = size_t(0); i < sz; i++) {
//        const auto& item = v[i];
//        cout << item << " ";
//    }
}


int main()
{

    auto v = vector<int>{1,2,3,10,20};
//    transform<int,OneInter>(v, &dosmt2);
//    transform(v, &dosmt2);
    auto obj = IncrementByKMulM(5,2);
    transform(v, obj);
    print(v);

    auto l = list<int>{1,2,10,20};
    print(l);
//    transform<int,OneInter>(l, &dosmt2); // it is not work now because it works only with vectors
//    transform(l, &dosmt2);
    transform(l, obj);

    // using lambda to cunstruct Object at the compiler time
    transform(v, [K=5, M=10](int a) { return (a+K)*M; } );
    print(v);
    print(l);
    return 0;
}
