// C has malloc and free for dynamic memory handling.
// C++ has new/delete.
// Vector object with dynamic dimensions
// static variables, static member variables
// Generic Programming = Templates in C++

// const keyword

// OOP:
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment (in CS409/509 Adv. C++ Course)
// inheritance (later)

// function overloading
// operators and operator overloading
// function parameters: pass by value, pass by reference

// auto, AAA rule (almost always auto)

#include <iostream>

using namespace std;

// it is a free vairable so it is not a good way
int a = 10; // static initialization

template <typename T>
struct Vector {
    int size;
    T* data;

    Vector(int size, T* initial_val) : size(size), data(new T[size]) {
        for (int i = 0; i < size; i++)
            data[i] = initial_val[i];
    }

    // You should use destructor to free pointer object
    ~Vector() {
        delete[] data;
    }

    void setIndex(int index, T value) {
        Vector& iv = *this;

        this->data[index] = value;
    }

    // But print function should be more general (free func)
    void print() const {
        for (int i = 0; i < size; i++) {
            cout << this->data[i];
            if (i != size-1)
                cout << ", ";
        }
        cout << endl;
    }
};

template <typename T>
void print(const Vector<T>& iv) {
    static bool first = true;

    if (first) {
        cout << "hi i am initialized first time" << endl;
        first = false;
    }


    for (int i = 0; i < iv.size; i++) {
        cout << iv.data[i];
        if (i != iv.size-1)
            cout << ", ";
    }
    cout << endl;
}


int main()
{

    {
        int iv_values[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto iv = Vector<int>(10, &iv_values[0]);
        iv.data[2] = 5;

        iv.setIndex(3,7);
        iv.setIndex(4, 8);
        iv.print();

        print(iv);
        print(iv);

        {
            cout << "Double Vectors: " << endl;
            double dv_values[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
            auto dv = Vector<double>(5, &dv_values[0]);

            print(dv);
        }
        // print(dv); // you can't use dv outside the curly brackets because it is freed
    }


    // ptr in the stack but memmory adress in the heap
    int* ptr = (int*)malloc(sizeof(int)*100); // malloc is a void pointer(void*) so it does not know memmory adress

    cout << ptr << endl; // memmory address

    ptr[0] = 1; // assigning value to adress in the firs part of the allocated memory
    cout << ptr[0] << endl;

    ptr[-1] = 10; // out of bound in the old version
    cout << ptr[-1] << endl;

    *(ptr + 10) = 5;
    cout << *(ptr+10) << endl;

    //free(ptr); // to free the from the stack memory (at the end of the main func it will be free if you don't free in here)

    // Using curly brackets mean after the bracket the memory will bw free

    return 0;
}
