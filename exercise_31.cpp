// app1:
// CRTP: curiously recurring template pattern (compile time polymorphism)

// app2: design patterns:
// singleton, factory, observer

// app3:
// RAII (Resource Acquisition is Initialization)

// app4:
// std::optional

// app5:
// multi threading, std::thread

// app6:
// multi threading, mutex

// app7:
// future, promise, std::async

// app8:
// chrono, random, atomics

#include <iostream>

using namespace std;

template <typename Derived> // Derived is equal to any class that is derived from Base
struct Base {
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

struct Derived : Base<Derived> {
    void implementation() {
        // implementation details
        cout << "i amd the derived and use me for plugin" << endl;
    }
};

int main() {
    auto d = Derived{}; // AAA notation
    d.interface();  // Calls Derived::implementation


}
