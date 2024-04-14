// perfect forwarding

// Node<T> implementation with virtual functions + inheritance
// a List<T> implementation, go low-level, then implement with standard library
// move-ctor, move-assignment


#include <iostream>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!


struct NodeBase {
    NodeBase* next = nullptr;

    virtual void printYourself() = 0;  // this is the 0th index at vtable
    virtual ~NodeBase() {}
};


template<typename T>
struct Node : NodeBase {
    T str;

    Node(const T& str) : str(str) { cout << "Copy c-tor: (" << &this->str << ", " << this->str << ")" << endl; };  // Copy c-tor
    Node(T&& str) : str(std::move(str)) {cout << "move c-tor: (" << &this->str << ", " << this->str << ")" << endl;}; // move c-tor

    void printYourself() override {
        cout << str << endl;
    }
};

struct List {
    NodeBase* head = nullptr;

    List() { }
    List(NodeBase* head) : head(head) { }

    void push(NodeBase* ptr) {
        ptr->next = head;
        head = ptr;
    }
};


void print(const List& l) {
    auto* node = l.head;

    while(node) {
        node->printYourself();
        node = node->next;
    }
}

int main(int argc, char* argv[])
{
    auto* node1_ptr = new Node(string("hello")); // string(hello) is a r-value

    auto k = string("world");
    cout << "original address of the copy c-tor: " << &k << endl;
    auto* node2_ptr = new Node<string>(k); // k is an l-value -> copy c-tor will be called

    auto* list = new List();
    auto* list2 = new List(node2_ptr);

    list->push(node2_ptr);
    list->push(new Node<string>("Blabla"));
    // (*list).push(node2_ptr);
    list->push(new Node<int>(10));

    print(*list);

    delete list;
    delete  list2;
    return 0;
}
