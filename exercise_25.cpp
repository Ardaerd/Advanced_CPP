// decltype(auto)

// get_int_byval(), get_int_byref()
// function object that calls the callable when called :)

// Tuple struct implementations

// lambdas capturing local variables: this includes local parameter packs as well
// storing parameter packs: an elegant storage container; get_first, get_size, get_tail impl.

// std::function<...> // type erasure

#include <iostream>

using namespace std;

// in here we are automatically casting return type to int
// if you return float number it will automatically cast to int
auto get_int_byval() -> int { int i = 5; return i; }

// now we are automatically returning to reference of the returned value
// we are using static to extend the life time of the variable
auto get_int_byref() -> int& { static int i = 5; return i; }

template<typename...>
struct Debug;

int main() {

    auto value1 = get_int_byval(); // type->int
    // auto is deduced to type of the value. You should do auto&
    auto value2 = get_int_byref(); // stil type -> int

    // you shoud use decltype(auto)
    decltype(auto) value3 = get_int_byval();
    decltype(auto) value4 = get_int_byref();

    auto t = Debug<decltype(value4)>{};

    return 0;
}
