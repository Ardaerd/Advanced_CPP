#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <variant>

using namespace std;

template<typename ...> struct TD;

template<typename T>
struct Mat {
    using type = T;
    size_t rows, cols;
    vector<T> data;

    Mat(size_t rows = 0, size_t cols = 0, T init = T{}) : rows{rows}, cols{cols}, data(rows*cols, init) { }

    const T* operator[](size_t r) const { return &data[r*cols]; }
    T* operator[](size_t r) { return &data[r*cols]; }

};


template<typename T>
void print(const Mat<T>& m) {
    for (size_t i = 0; i < m.rows; i++) {
        auto ptr = m[i];

        for (size_t j = 0; j < m.cols; j++) {

            if constexpr(is_same_v<string,T>)
                cout << "\"" << ptr[j] << "\" ";
            else
                cout << ptr[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


template<typename T>
concept IsMatX = is_same_v<Mat<typename remove_reference_t<T>::type>, remove_reference_t<T>>;


template<IsMatX T>
auto transform(T&& mat_src, auto func) {
    using M = remove_reference_t<T>; // Mat<U> with reference filtered out
    using U = typename M::type; // underlying type stored in Mat
    using V = remove_cvref_t<decltype(func(U{}))>; // Underlying type after the transformation

    if constexpr(is_reference_v<T>)
        cout << "Transforming l-value parameter" << endl;
    else
        cout << "Transforming r-value parameter" << endl;

    auto mat_dest = Mat<V>{mat_src.rows, mat_src.cols};

    for (size_t i = 0; i < mat_src.rows; i++) {
        auto src_ptr = mat_src[i];
        auto dest_ptr = mat_dest[i];

        for (size_t j=0; j<mat_src.cols; j++)
            dest_ptr[j] = func(src_ptr[j]);
    }

    return mat_dest;
}

int main()
{
    // LIMITATION! For Q1a and Q1b in total, you can use at most 6 semicolon (;) characters
    // including the struct ending semicolon
    // Q1a - Create a Mat<T> class with a c-tor of Mat(rows, cols, initial_value)
    // T is automatically deduced from the initial_value's type
    auto m1 = Mat(2, 3, 9.9); // 2 row, 3 column matrix with double values is initialized to 9.9 for each cell
    print(m1);

    // Q1b - Make below assignment style work (i.e. m1[rowindex][colindex])
    for(size_t i=0; i<m1.rows; ++i)
        m1[i][i] = 1.1;

    auto m2_ = Mat(2, 3, "Hello"); // 2 row, 3 column matrix with double values is initialized to 9.9 for each cell
    print(m2_);

    // Q1b - Make below assignment style work (i.e. m1[rowindex][colindex])
    for(size_t i=0; i<m2_.rows; ++i)
        m2_[i][i] = "World";

    // Q1c - write a print free-function that prints an instance of Mat<T>
    // if T is string, it puts " around the value, otherwise it directly prints the value
    print(m1);
    print(m2_);

    // Q2 - Write a "auto transform(const Mat<T>& mat_src, auto&& func)" free-function
    // that can take a source matrix and transform its contents globally.
    // At the end it returns the transformed matrix. Original matrix stays untouched.
    // Returned matrix can be of a different type depending on the "func"'s return value.
    // i.e. Mat<int> after transformation can be Mat<double> for instance.
    auto m2 = transform(
        Mat{2, 1,
            map<string, variant<string, double, int>>{
                {"pi", 3.14},
                {"CS", "409/509"},
                {"year", 2021}
            }
        }, []<typename T>(T&& map_) {
            auto s = string{};
            for(const auto& [key, value] : map_)
            {
                auto value_str = string{};

                if(holds_alternative<string>(value))
                    value_str = get<string>(value);

                else if(holds_alternative<double>(value))
                    value_str = to_string(get<double>(value));

                else if(holds_alternative<int>(value))
                    value_str = to_string(get<int>(value));

                s += key + ": " + value_str + " ";
            }
            return s;
        });

    print(m1);
    print(m2);

//    // Q3a - Write a SINGLE (overloading inc is not allowed) free-function named "inc".
//    // writing overloads for inc function will get you zero points
//    // This function returns a new Mat<T> whose contents are incremented by 1.
//    // It also writes l-value or r-value to the console based on its parameter's situation at the call site.

//    // Q3b - Make the SINGLE "inc" function available only for Mat<T> types using concepts
//    // writing overloads for inc function will get you zero points
//    // For instance, Mat<string> cannot be incremented. Mat<int>, Mat<float>, ... can be incremented.
//    print(inc(m1)); // prints l-value
//    print(inc(Mat(1, 4, 1))); // prints r-value


//    // Q4 - Write a concat struct that can concatenate tuples at least as described below
//    // concat omits the void at the end
//    // concat concatenates types of two tuples into one tuple
////    using T1 = tuple<int, double, float>;
////    TD< concat_t<T1, void> > q4a; // ---> tuple<int, double, float>
////    TD< concat_t<T1, T1> > q4b; // ---> tuple<int, double, float, int, double, float>


//    // Q5 - Write IsIntegral value-trait which is similar to std::is_integral.
//    // But your implementation must also accept IsIntegral<> as a valid entry.
//    // i.e. <> means an empty parameter-pack

//    // Q6 - Write "filter_types" type-trait
//    //  that accepts a value-trait and many types
//    //  as a value trait you must support at least both of IsIntegral<> and is_integral<void>
//    //  a value-trait can be, for instance, IsIntegral that checks if a type is suitable or not
//    //  in the end, filter_types struct supplies the types filtered according to the value-trait in its "type" attribute
//    //  Note: shortcut usage filter_types_t is already supplied for you
//    //  Do not write templated classes in the main() function block. Leave them in the global namespace.
//    using TUPLE = tuple<int, float, string, char, short, double, string, double, float>;

//    using TUPLE_INTEGRAL = filter_types_t<IsIntegral<>, TUPLE>;
////    TUPLE_INTEGRAL --> tuple<int, char, short>
////    TD< TUPLE_INTEGRAL > q6a;

//    using TUPLE_FLOATING = filter_types_t<is_floating_point<void>, TUPLE>;
////    TUPLE_FLOATING --> tuple<float, double, double, float>
////    TD< TUPLE_FLOATING > q6b;

//    // Q7 - Write a "transform_types" type trait
//    //  that accepts convertion type-trait and many types
//    //  a type-trait specialized for your scenario is already supplied. Its called "Transformer".
//    //  in the end, transform_types struct supplies the transformed types according to the type-trait in its "type" attribute
//    //  Note: shortcut usage transform_types_t is already supplied for you
//    //  Do not write templated classes in the main() function block. Leave them in the global namespace.

//    using TUPLE_TRANSFORMED = transform_types_t<Transformer<>, TUPLE>;
////    TUPLE_TRANSFORMED --> tuple<int, float, String, int, int, float, String, float, float>
////    TD< TUPLE_TRANSFORMED > q7a;

//    // Q8 - Write a constexpr free-function named count_types
//    // when used as shown below it returns the number of types in a tuple that fits to the criterion supplied
//    cout << "Number of integral types in TUPLE is " << count_types<IsIntegral>(TUPLE{}) << endl;
//    cout << "Number of integral types in TUPLE is " << count_types<is_integral>(TUPLE{}) << endl;
//    cout << "Number of floating types in TUPLE is " << count_types<is_floating_point>(TUPLE{}) << endl;

    return 0;
}
