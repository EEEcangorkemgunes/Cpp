#include <iostream>
#include <type_traits>
#include <typeinfo>


// how to do all operations dynamically? return type and operations

template <bool T>
typename std::conditional<T, int, double>::type foo() {
  if constexpr (T) {
    return 5;
  } else {
    return 5.5;
  }
}

int main() {
  std::cout << foo<true>() << std::endl;
  std::cout << foo<false>() << std::endl;
  return 0;
}