// compile time binding
// static polymorphism can be achieved by using templates and function
// overloading
#include <iostream>
void print(int i) { std::cout << "Printing int: " << i << std::endl; }
void print(double f) { std::cout << "Printing float: " << f << std::endl; }
void print(char const* c) {
  std::cout << "Printing character: " << c << std::endl;
}

int main() {
  print(5);
  print(500.263);
  print("Hello C++");
  print(5);
  return 0;
}