// Write a HeapValue<T> class that uses heap memory for storage! with all ctors and dtors
// move-ctor, move-assignment

// initializer_list<T>


#include <iostream>
#include <string>
#include <vector>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T>
struct HeapValue {
  T* ptr = nullptr;

  HeapValue() : ptr(new T{}) {}
  HeapValue(const T& t) : ptr(new T{t}) { cout << "old style ctor called!" << endl; }
  // copy ctor
  HeapValue(const HeapValue<T>& other) : ptr(new T{*other.ptr}) { cout << "Copy ctor is called!" << endl; }
  // move ctor
  HeapValue(HeapValue<T>&& other) : ptr(other.ptr) {
      other.ptr = nullptr;
      cout << "Move assignment called: " << other.ptr << " -> " << ptr << endl;
  }

  // new style c-tor accessible by curly brackets
  HeapValue(std::initializer_list<T> content) : ptr(new T{*content.begin()}) {
      cout << "new ctor is called with size of " << content.size() << endl;

      if (!content.size()) {
              cout << "The list is empty." << endl;
          } else {
              cout << "Contents: ";
              for (const auto& item : content) {
                  cout << item << " ";
              }
              cout << endl;
          }
  }

//  HeapValue(T& t) : ptr(new T{t}) {}
//  HeapValue(T&& t) : ptr(new T{t}) {}

  void print() {
      cout << "Value: " << *ptr << endl;
      cout << "Adress: " << ptr << endl;
  }

  // destructor called when local scopes ends
  ~HeapValue() {
      cout << "HeapValue object is destructed!" << endl;
      cout << "Address of destructed variable: " << ptr << endl;
      delete ptr;
  }
};

int main(int argc, char* argv[])
{

    // it is in the stack
    auto a = 5;

    // we are allocating memory from heap for ptr variable
    cout << "i" << endl;
    auto i = HeapValue<int>{3};
    i.print();

    // j destructor is called when local scopes ends
    {
        cout << "j" << endl;
        auto j = HeapValue<int>{5};
        j.print();
    }

    cout << "s" << endl;
    auto s = HeapValue<string>{"5sdfasfewR3"};
    s.print();

    // HeapValue object is now living in the heap
    cout << "X" << endl;
    auto* x = new HeapValue<int>{};
    x->print();
    // dereferencing pointer and then accessing the member.
    (*x).print();
    delete x;

    cout << "s2" << endl;
    auto s2 = s; // s2 is being constructed
    s2.print();

    // Move ctor
    cout << "s3" << endl;
    auto s3 = (HeapValue<string>&&)s2;
    s3.print();

    // std move ctor
    cout << "s4" << endl;
    auto s4 = std::move(s3);
    s4.print();

    cout << "s5" << endl;
    auto s5 = HeapValue<int>{1, 2, 3, 4, 10, 20};

    cout << "s6" << endl;
    auto s6 = HeapValue<int>(1);

//    auto s5 = std::vector<int>{10}; // // size is 1 integer. that integer is 10
//    auto v2 = std::vector<int>(10); // size is 10 integers. all integers are default constructed

    cout << endl;
    return 0;
}
