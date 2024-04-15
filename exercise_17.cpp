// variadic templates, parameter packs, pack expansions (C++11 and later) "modern C++"
// - write an add function that adds all its input parameters

// fold expressions (C++17 and later) "more modern C++" ---> "modern C++"
// - write an add function that adds all its input parameters with fold expressions

// fold expressions and comma operator
// - write a print(...) function that prints all its input arguments to the console

// std::pair, std::tuple, std::map
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>

using namespace std;

// this can work both compile and run time
template<typename T1, typename T2>
auto add_v1(T1 a, T2 b) { return a + b; }

// This is puerly work in compile time
template<auto a, auto b>
auto add_v2() { return a + b; }

// Ts is called a compile time parameter-pack
template<typename ... Ts> // Ts is int|double|float
auto add_v3(Ts ... ts) { // ts is now a run time parameter-pack: 1|1.1|2.2f
    return (ts + ...);
}

// this is called a compile time parameter pack
auto add_v4() { return 0; }

template<typename First, typename ... Rest>
auto add_v4(First first, Rest ... rest) {
    return first + add_v4(rest...); // pack expansion
}


// inline for according to the recursive call copy and paste function
template<typename First, typename ... Rest>
inline auto add_v5(First first, Rest ... rest) {
    if constexpr(sizeof...(rest) == 0)
        return first;
    else
        return first + add_v5(rest...);
}

template<typename ... Ts>
inline auto add_v6(Ts ... ts) {
    return (ts + ...);
}


int main(int argc, char* argv[])
{
    cout << add_v1(5, 5.3) << endl;
    cout << add_v2<5, 5.3>() << endl;
    cout << add_v3<>(5.3, 5, 6.2f) << endl;
    cout << add_v4<>(5.3, 5, 6.2f) << endl;
    cout << add_v5(1, 1.1, 2.2f, 10) << endl;
    cout << add_v6(1, 1.1, 2.2f, 10) << endl;


    return 0;
}
