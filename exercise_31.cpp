// [[nodiscard]], std::unique_ptr, std::shared_ptr
// duck typing? type erasure: std::function
// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern

#include <iostream>
#include <memory>

using namespace std;

[[nodiscard]] int foo() {
    return 1;
}

// The [[nodiscard]] attribute can help prevent resource leaks by making sure the return value of functions that return a std::unique_ptr is               not ignored.
//std::unique_ptr supports move semantics but does not support copy semantics. This means you can transfer ownership of the resource by moving the std::unique_ptr, but you cannot copy it.
[[nodiscard]] unique_ptr<int> bar(unique_ptr<int> i) {
    return std::move(i);
}


int main() {
//     foo(); // this warns you so that the return value cannot be ignored

     auto i_ptr = unique_ptr<int>(new int(10));
     cout << "Addres: " << i_ptr << endl;
     cout << "Value: " << *i_ptr << endl;

     auto i_ptr_make = make_unique<int>(15);
     cout << "Addres: " << i_ptr_make << endl;
     cout << "Value: " << *i_ptr_make << endl;

     auto i_ptr2_make = unique_ptr<int>(std::move(i_ptr_make));
     cout << "Addres: " << i_ptr2_make << endl;
     cout << "Value: " << *i_ptr2_make << endl;

     auto i_ptr2 = std::move(i_ptr); // copy ctor is in "= delete" state
     cout << "Addres:" << i_ptr2 << endl;
     cout << "Value:" << *i_ptr2 << endl;

     auto i_ptr3 = unique_ptr<int>(std::move(i_ptr2));
     cout << "Addres: " << i_ptr3 << endl;
     cout << "Value: " << *i_ptr3 << endl;

     auto j = bar(std::move(i_ptr3));
     cout << "Addres:" << j << endl;
     cout << "Value:" << *j << endl;

     // there is a count attribute in shared pointer and if different variable access this pointer it increment counter,
     // if counter is zero it destroy pointer automatically
//     auto s_ptr = shared_ptr<int>(new int(101));
     auto s_ptr = make_shared<int>(101);
     auto s_ptr2 = s_ptr; // c-tor for pointer

     cout << "Addres:" << s_ptr << endl;
     cout << "Value:" << *s_ptr << endl;

     cout << "Addres:" << s_ptr2 << endl;
     cout << "Value:" << *s_ptr2 << endl;


    return 0;
}
