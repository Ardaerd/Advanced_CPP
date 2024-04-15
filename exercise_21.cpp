// Function objects, operator() overloads and multiple inheritance
// lambda equivalents and the "struct overloaded { ... }" trick
// std::variant

#include <iostream>
#include <variant>

using namespace std;

template<typename T>
struct Value {
    T value;

    operator T() { return value; }
};

// we can downcast double to int
struct FuncObjInt {
    void operator() (int a) const {
        cout << "This value is an integer " << a << endl;
    }
};

// we can downcast double to float
struct FuncObjFloat {
    void operator() (float a) const {
        cout << "This value is a float " << a << endl;
    }
};


// Which one should we downcast int or float (error ambigous for double)
//struct FuncObjIntFloat {
//    void operator() (int a) const { cout << "This value is an integer " << a << endl; }
//    void operator() (float a) const { cout << "This value is an float " << a << endl; }
//};

// doing same thing like above with OOP style
struct FuncObjIntFloat : FuncObjInt, FuncObjFloat {
    using FuncObjInt::operator(), FuncObjFloat::operator();
};

// this is a more generic way to do above things
template<typename ... FuncObjs>         // FuncObjInt|FuncObjFloat
struct FuncObjGeneric : FuncObjs... {
    using FuncObjs::operator()...;
};


template<typename ... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

using Double = Value<double>;
using Float = Value<float>;

int main(int argc, char* argv[])
{
    {
        auto fo_int = FuncObjInt{};
        auto fo_float = FuncObjFloat{};
        auto fo_int_float = FuncObjIntFloat{};

        fo_int(5);
        fo_float(3.14);
    //    fo_float(Double{3.14});
        fo_int_float(3.14f);

        auto fo_generic = FuncObjGeneric<FuncObjInt, FuncObjFloat>{};
        fo_generic(5);
        fo_generic(5.12f);
    }

    // doing the above things with lambda
    auto lambda_int = [](int a) { cout << "This value is an integer " << a << endl; };
    auto lambda_float = [](float a) { cout << "This value is an float " << a << endl; };

    lambda_int(51);
    lambda_float(51.12f);

    {
        // doing the same things with more generic lambda
        auto lambda_intfloat = []<typename T>(T a) {
            if constexpr(is_same_v<T,int>)
                cout << "This value is an integer " << a << endl;
            else if constexpr(is_same_v<T,float>)
                cout << "This value is an float " << a << endl;
        };

        lambda_intfloat(12);
        lambda_intfloat(12.23f);
    }

    auto x = Overloaded{lambda_int, lambda_float};

    x(21);
    x(21.2f);

    auto var = variant<int, float>{};

    var = 5;
    std::visit(x, var);

    var = 5.12f;
    std::visit(x, var);


    return 0;
}
