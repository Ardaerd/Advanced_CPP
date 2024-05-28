// std::integral_constant, std::true_type, std::false_type, tag dispatching

// constexpr functions
// std::is_constant_evaluated()

// godbolt.org
// factorial function that runs at compile time
// - with integral_constant
// - with constexpr

// decltype(auto)

#include <iostream>
// #include <string>

using namespace std;

//// It was an run time code
//void log(auto smt, bool logging) {
//    if (logging) cout << "Logging: " << smt << endl;
//    else cout << "Release: " << smt << endl;
//}

// now it is like a compile time switch case statement but it is not perfect yet
//void log(auto smt, int) { cout << "Logging: " << smt << endl; }
//void log(auto smt, float) { cout << "Logging: " << smt << endl; }

struct LoggingMode { };
struct ReleaseMode { };

// This is called tag dispatching
void log(auto smt, LoggingMode) { cout << "Logging: " << smt << endl; }
void log(auto smt, ReleaseMode) { cout << "Release: " << smt << endl; }

// you can use this instead of specifiying function type in ate beggining
//auto foo() -> int {
//    return 10;
//}

// now we are saying compiler can you do this operation
// at compile time and plug it were we call it (no extra function needed)
constexpr auto foo() -> int {
    return 10;
}

// you can make it general
struct int_10 {
    using type = int;
    static constexpr int value = 10;
};

struct float_3_14f {
    using type = float;
    static constexpr float value = 3.14f;
};

//template<typename T, T v>
//struct Constant {
//    using type = T;
//    static constexpr T value = v;
//};

template<auto v>
struct Constant {
    using type = decltype(v);
    static constexpr decltype(v) value = v;
};


//const int i = 20;
constexpr int i = 20;

int main() {
//    auto v = int_10::value;
//    auto z = float_3_14f::value;

//    cout << v << endl;
//    cout << z << endl;

//    auto v2 = Constant<int, 10>::value;
//    auto z2 = Constant<float, 3.14f>::value;

//    cout << v2 << endl;
//    cout << z2 << endl;

    auto v3 = Constant<12.3f>::value;
    cout << v3 << endl;


    log("Whatever", LoggingMode{});
    log("hi there", ReleaseMode{});

    int* p = (int*)&i;
    cout << "p: " << *p << endl;
    cout << "i: " << i << endl;

    return 0;
}
