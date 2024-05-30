// tuple implementation

//auto const get() {}: The function itself is not const, meaning it can modify the state of the object. However, the return value is const, meaning it cannot be modified.
//auto get() const {}: This is a const member function, meaning it guarantees not to modify any member variables of the object (unless they are marked as mutable). The return value is not necessarily const (unless it is explicitly specified).

#include <iostream>
#include <variant>
#include <tuple>

using namespace std;

// we are doing this operation in compile time with using template structure
template<typename First, typename ... Rest>
struct Tuple {
    First value;
    Tuple<Rest...> rest;

    template<size_t target_idx, size_t current_idx = 0>
    auto get() const {
        if constexpr(target_idx == current_idx)
            return value;
        else
            return rest.template get<target_idx, current_idx+1>();
    }

    template<typename target_type>
    auto get() const {
        if constexpr(std::is_same_v<target_type, First>)
            return value;
        else
            return rest.template get<target_type>();
    }
};

template<typename T>
struct Tuple<T> {
    T value;

    template<size_t target_idx, size_t current_idx = 0>
    auto get() const {
        // this is a compiler time assertion
        static_assert(target_idx == current_idx, "Error: Couldn't found the index");

        return value;
    }

    template<typename target_type>
    auto get() const {
        static_assert(std::is_same_v<target_type, T>, "Error: Type couldn't found!");

        return value;
    }
};


template<typename target_type, typename ...Ts>
auto get(const Tuple<Ts...>& t) {
    return t.template get<target_type>();
}

template<size_t target_idx, typename ...Ts>
auto get(const Tuple<Ts...>& t) {
    return t.template get<target_idx>();
}

int main()
{
    auto t = Tuple<int, float, double>{2, 1.1f, 3.14};
    cout << "idx_0: " << t.get<0>() << endl;
    cout << "idx_1: " << t.get<1>() << endl;
    cout << "idx_2: " << t.get<2>() << endl;
//    cout << "idx_3:" << t.get<3>() << endl; // compile time error generated

    cout << "Double variable: " << t.get<double>() << endl;
    cout << "Integer variable: " << t.get<int>() << endl;
    cout << "Float variable: " << t.get<float>() << endl;
//    cout << "String variable: " << t.get<char>() << endl; // compile time error generated

    cout << "Double called with free function: " << get<double>(t) << endl;
    cout << "Integer called with free function: " << get<int>(t) << endl;
    cout << "Float called with free function: " << get<float>(t) << endl;

    cout << "idx_0 called with free function: " << get<0>(t) << endl;
    cout << "idx_1 called with free function: " << get<1>(t) << endl;
    cout << "idx_2 called with free function: " << get<2>(t) << endl;

    return 0;
}

//struct X {
//    int i; // assigned 2
//    float f; // asigned 1.1f
//    double d; // assigned 1, became 1.0

//    // now it is a compile time get function
//    template<size_t idx>
//    auto get() const {
//        if constexpr(idx == 0) {
//            return i;
//        }
//        else if constexpr(idx == 1) {
//            return f;
//        }
//        else if constexpr(idx == 2) {
//            return d;
//        }
//    }


    // it gets inconsistent type error because auto can't decide which return type should have
    // therefore we should use variant
//    auto get(size_t index) const -> std::variant<int, float, double> {
//        switch (index) {
//        case 0: return i;
//        case 1: return f;
//        case 2: return d;
//        default: return 0;
//        }
//    }
//};
