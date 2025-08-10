#include <iostream>
#include <utility>

// Forwarding ref = T&& where T is deduced (template param or auto)
//   - Can bind to lvalues & rvalues via reference collapsing
//   - Use std::forward<T>(arg) to preserve original category when passing along
// Plain rvalue ref = Type&& (non-deduced) → binds rvalues only → use std::move

// Benefits: One template handles both lvalues & rvalues, avoids copies,
// moves rvalues, works with move-only types

// Examples:
//  template<class T> void f(T&& x) { callee(std::forward<T>(x)); } // forwarding
//  template<class T> void g(std::vector<T>&& v) { sink(std::move(v)); } // plain rvalue reference
//
// Move example:
//  void take(std::string&& s) {
//      use(s);               // s is an lvalue → copy
//      use(std::move(s));     // s is rvalue → move
//  }
//  
//  template<class T>
//  void wrap(T&& x) {
//      use(std::forward<T>(x)); // rvalue at call site → move, lvalue → copy
//  }

int a{};
f(a);   // lvalue → lvalue
f(5);   // rvalue → rvalue

// std::forward<T> implementation from scratch
template<typename T>
constexpr T&& forwardCustom(std::remove_reference_t<T>& t) noexcept { // restore l value
    return static_cast<T&&>(t);
}

template<typename T>
constexpr T&& forwardCustom(std::remove_reference_t<T>&& t) noexcept { // restore r value
    return static_cast<T&&>(t);
}

// T&& std::forward<T> preserves the original value category of a forwarding ref:
// - T = U&  T&& = (U&)&& → returns U& (lvalue)
// - T = U   T&& = (U&&)&& → returns U&&  (rvalue)
// remove_reference_t<T> is only for the param type; T keeps its refs for return type

void print_rlvalue(int&) { std::cout << "lvalue" << '\n'; }
void print_rlvalue(int&&) { std::cout << "rvalue" << '\n'; }

template<typename T>
void wrapper_no_forward(T&& arg) { 
    print_rlvalue(arg); 
}

template<typename T>
void wrapper_forward(T&& arg) { 
    print_rlvalue(std::forward<T>(arg));
}

template<typename T>
void wrapper_forwardCustom(T&& arg) { 
    print_rlvalue(forwardCustom<T>(arg));
}

int main()
{
    int x = 10;
    wrapper_no_forward(10); // lvalue
    wrapper_no_forward(x); // lvalue

    wrapper_forward(10); // rvalue - keep source type of arg 
    wrapper_forward(x); // lvalue - keep source type of arg 

    wrapper_forwardCustom(10); // rvalue - keep source type of arg 
    wrapper_forwardCustom(x); // lvalue - keep source type of arg 

    return 0;
}
