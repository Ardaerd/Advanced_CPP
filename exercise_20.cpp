// Array<T, sz> implementation with deduction guides


// Function objects, operator() overloads and multiple inheritance

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors

// lambda equivalents and the "struct overloaded { ... }" trick

// std::variant

#include <iostream>
#include <array>

using namespace std;

template<typename T, size_t sz>
struct Array {
    T data[sz];

    Array(initializer_list<T> values) {
        const auto s = values.size();
        auto* ptr = values.begin();

        for (auto i=0; i<sz; i++) {
            data[i] = *ptr;
            cout << data[i] << ", ";
            ptr = (ptr+1);
        }
        cout << endl;
    }
};


// we can use c-tor without explicitly specifying the template arguments
template<typename T>
Array(initializer_list<T> values) -> Array<T,2>;

Array(const char*) -> Array<string, 2>;

int main(int argc, char* argv[])
{
    int a[] = {1,2,3};

//    auto A = array<int,3>{1,2,3};

    auto A = Array<int, 3>{1,2,3};
    auto A2 = Array{1,2,3};
    auto A3 = Array{"hi there", "hello world"};

    return 0;
}
