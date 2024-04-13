#include <iostream>

// operator overloading
// function-call operator
// function objects
// function pointers

// returning a reference
// l-value, r-value, r-value binding reference
// repeat-it algorithm

// copy-ctor, copy-assignment
// move-ctor, move-assignment

using namespace std;

// overloading vs overriding
struct STRING {
    char* data;
    STRING() { data = new char[1]; data[0] = 0; }

    void operator=(const char* value) {
        // ...
    }
};


struct COUT {
    string name;

    void operator<<(int value) {
        auto& self = *this;
        self.name = "blabla";

        cout << value;
    }
};

COUT console;

auto lambda_console = [name=string("blabla")]() {
  cout << "Hi there " << name << endl;
};

int main(int argc, char* argv[])
{
    console.operator<<(5);
    lambda_console();

}
