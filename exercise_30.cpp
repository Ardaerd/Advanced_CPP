// = default, = delete, std::declval
// [[nodiscard]], std::unique_ptr, std::shared_ptr
// duck typing? type erasure: std::function
// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern

#include <iostream>

using namespace std;


#include <iostream>
#include <optional>
#include <vector>

struct Bar {
    // void* v_table
    Bar() { }

    virtual void print() const {
        cout << "I am bar" << endl;
    }

    void doIt() const {
        cout << "Just do it" << endl;
    }
};

struct Foo : Bar {
    // void* _vtable
    int i;
    float f;

    Foo() : i{10}, f{20.2f} {
        i = f + 1.0;
        cout << i << endl;
    }

    Foo(const Foo& other) = default;
    Foo(Foo&& other) = default;

    void print() const override {
        cout << "I am Foo" << endl;
    }

    void doIt() const = delete;
};

int main()
{
    auto inst1 = Foo();
    auto inst2 = Bar();

    // static_cast<T>, dynamic_cast<T>, reinterpret_cast<T>, const_cast<T>
    auto* inst3 = (Bar*)&inst1; // auto deduces Bar
    auto* inst4 = &inst2; // auto deduces Bar

    inst3->print();
    inst4->print();

    inst2.doIt();
//    inst1.doIt(); // it is deleted
}

