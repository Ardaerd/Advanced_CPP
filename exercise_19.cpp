// concepts
// requires clause
// requires expression
// --- CastableToInt

// Function objects, operator() overloads and multiple inheritance

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors
// Array<T, sz> implementation with deduction guides

// lambda equivalents and the "struct overloaded { ... }" trick

// std::variant

#include <iostream>

template<typename T>
concept CastableToInt = requires (T t) {
        // imagine T is std::string, t is maybe "hi there"s, it's not
        // castable to int, concept return false
        (int) t;
};

// this one and one below only works with one type
//template<CastableToInt ... Ts>
//void print_intcasts(const Ts& ... ts) {

//}

//void print_intcasts(const CastableToInt auto& ... ts) {

//}


// these two approach can work many type
//template<typename First, typename ... Rest>
//requires CastableToInt<First>
//void print_intcasts(const First& f, const Rest& ... rest) {

//}


// In this approach you can access the value of the parameters (this approach more powerfull)
template<typename First, typename ... Rest>
void print_intcasts(const First& f, const Rest& ... rest)
requires CastableToInt<First>
{

}


int main(int argc, char* argv[])
{
    print_intcasts(5, 5.5, 5.5f);
    return 0;
}
