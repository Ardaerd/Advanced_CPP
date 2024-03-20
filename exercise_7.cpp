// OOP:
// inheritance
// dynamic polymorphism / virtual functions vs RTTI
// move-ctor, move-assignment

// functional programming:
// - overloading
//   (all the operators are implemented as functions and they also can ve overloaded)

// Generics / Templates:
// function, class, variable, type templates

#include <iostream>
#include <string>

using namespace std;


namespace Utils {
    int VALUE = 123;
}


struct Animal {
    string name;

    // it is a advance way because it directly construct it without overwritting.
    Animal(const string& name) : name(name) { }
    Animal() { }

    // This construction is not good because you are constructing name with nullptr and then overwrite it.
    // So it is extra burden
//    Animal(const string& name) {
//        this->name = name;
//    }

    virtual void whoAmI() { // this is the 0th index in the vtable
        cout << "I am an arbitrary animal." << endl;
    }
};

struct Dog : Animal {
    string breed;

    Dog(const string& name, const string& breed = "") : Animal(name), breed(breed) { }
    Dog() { }

    void whoAmI() override{
        cout << "I am a Dog." << endl;
    }
};

int main(int argc, char* argv[]) {

    using namespace Utils;
    using Utils::VALUE;
    cout << VALUE << endl;

//    cout << Utils::VALUE << endl;

    auto animal = Animal("Elephant");
    auto dog = Dog("Poopy", "Rotweiler");

    cout << "Size of Animal: " << sizeof(Animal) << endl;
    cout << "Size of Dog: " << sizeof(Dog) << endl;

    using AnimalPtr = Animal*;
    AnimalPtr animals[] = { &animal, &dog, &animal, &dog }; // each of them 8 byte

    cout << sizeof(animals) << endl;
    cout << sizeof(AnimalPtr) << endl;
    cout << sizeof(animals)/sizeof(AnimalPtr) << endl;

    auto size = sizeof(animals)/sizeof(AnimalPtr);

    for (auto i = 0; i < size; i++)
        animals[i]->whoAmI();

    return 0;
}
