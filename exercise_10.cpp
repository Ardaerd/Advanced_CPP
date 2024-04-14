#include <iostream>
#include <vector>

// r-value binding reference
// move-ctor, move-assignment
// very big object (heap allocation): legacy version, modern version

using namespace std;

void foo(int& a) { // this only binds to l-value
    a++;
    cout << "l-value is: " << a << endl;
}

//void foo(int a) { // this binds to l-value and r-value
//    a++;
//    cout << "Beccause of Clone l-value and r-value are: " << a << endl;
//}

void foo(int&& a) { // this only binds to r-value
    cout << "r-value is: " << a << endl;
}

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
