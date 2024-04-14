// perfect forwarding, about the extention done at 2011 dialect (r-value binding) &&

// Node<T> implementation with virtual functions + inheritance
// a List<T> implementation, go low-level, then implement with standard library
// move-ctor, move-assignment


#include <iostream>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T>
struct TypeDisplay; // forward declare, but don't give the declaration yet

template<typename T>
void bar(T&& k) {
    auto t = TypeDisplay<T>{};
}

// forwarding reference or previously called universal reference
template<typename T>
void foo(T&& whatever) {
    // if T is pure (no modifiers), it's a r-value at call site
    // if T contains ref, it's a l-value at call site
    // whatever itself is an l-value
    // auto t = TypeDisplay<T>{};
    //using Tpure = std::remove_reference<T>::type;
//    bar((Tpure&&)whatever);
    bar(std::forward<T>(whatever));
}

// If you don't do it like above you should repeat yourself like below
//void foo(int& t) { }
//void foo(int&& t) { }

int main(int argc, char* argv[])
{
    using intref = int&;
    using intrefref = int&&;

//    int a = 10;

//    foo(a);
//    foo(10);

    return 0;
}
