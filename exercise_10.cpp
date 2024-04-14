#include <iostream>
#include <vector>

// r-value binding reference
// move-ctor, move-assignment
// very big object (heap allocation): legacy version, modern version

using namespace std;


// Why does this bind only to l-values? The signature int& a means that foo takes an argument by non-const reference.
// Non-const references can only bind to modifiable l-values because:
// They need an existing object to refer to (something with a stable address).
// They potentially modify the object, so the referred object must be non-const.

void foo(int& a) { // this only binds to l-value
    a++;
    cout << "l-value is: " << a << endl;
}

//void foo(int a) { // this binds to l-value and r-value
//    a++;
//    cout << "Beccause of Clone l-value and r-value are: " << a << endl;
//}


// Why does this bind only to r-values? The signature int&& a means foo takes an argument by r-value reference.
// R-value references are designed to bind specifically to temporaries:
// They enable the function to operate on a temporary without creating a copy.
// They are often used for move semantics, which can significantly optimize performance by "moving" resources (like dynamically allocated memory)
// from temporaries to new owners.

void foo(int&& a) { // this only binds to r-value
    cout << "r-value is: " << a << endl;
}


// What does const reference mean here? When you use a const reference (const int& a), the function foo can accept both l-values and r-values:
// For l-values: It can bind to l-values (like variables) without risk of modification, hence preserving the constancy of user-defined variables.
// For r-values: It can also bind to r-values. Since the function does not modify the argument (guaranteed by the const qualifier), it's safe to bind to temporaries.
// This is useful because it prevents unnecessary copying of data.

void foo(const int& a) { // this binds to both l-value and r-value with ref
    cout << "const value is: " << a << endl;
}

int main(int argc, char* argv[])
{
    auto k = 10;
    foo(k);
    cout << k << endl;

    foo(10);
}
