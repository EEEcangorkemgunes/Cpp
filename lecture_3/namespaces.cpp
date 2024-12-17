
#include <iostream>
namespace A {
int k = 1;
int l = 2;
}  // namespace A

namespace B {
class asdf {
 public:
  int a = 1;
  asdf() { std::cout << "asdf constructor" << std::endl; }
  ~asdf() { std::cout << "asdf destructor" << std::endl; }
};
int x = 3;
int y = 4;
}  // namespace B

using namespace A;
int main() {
  std::cout << k << l << std::endl;
  std::cout << B::x << B::y << std::endl;

  return 0;
}