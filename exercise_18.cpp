// std::pair, std::tuple, std::map, structured binding
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>
#include <string>
#include <map>

using namespace std;

template<typename First, typename Second>
struct Pair {
    First first;
    Second second;

//    Pair(First f, Second s) : first(f), second(s) {
//        cout << "(" << first << ", " << second << ")" << endl;
//    }

//    template<typename T, typename K>
    constexpr Pair(First&& first, Second&& second) : first{forward<First>(first)}, second{forward<Second>(second)} {
        cout << "(" << this->first << ", " << this->second << ")" << endl;
    }
};


template<typename K, typename V>
void print(const map<K, V>& m) {
//    for (auto it = m.begin(); it != m.end(); it++)
//        const auto& item = *it;

//    for (const auto& item : m) {
//        const auto& key = item.first;
//        const auto& value = item.second;
//        cout << "Key - Value: " << "(" << key << ", " << value << ")" << endl;
//    }

    for (const auto& [key, value] : m) { // structered binding
        cout << "Key - Value: " << "(" << key << ", " << value << ")" << endl;
    }
}


template<typename ... Ts>
void print(const tuple<Ts...>& ts) {
    const auto size = sizeof...(Ts);
    cout << "tuple has " << size << " dimensions." << endl;

    // this is a compile time for loop
    ((cout << get<Ts>(ts) << endl), ...);

// this for loop is run time but we should do the for in compile time
//    for (auto i = 0; i < size; i++)
//        cout << get<i>(ts) << endl;
}

int main(int argc, char* argv[])
{
//    auto p = Pair{"key", 10};
    auto p = Pair<string, int>{"key", 10};

    auto m = map<int,string> {
        {1, "one"},
        {2, "two"}
    };

    print(m);

    auto t = tuple<int, float, string>{5, 3.14f, "hi there"};
    print(t);

    return 0;
}
