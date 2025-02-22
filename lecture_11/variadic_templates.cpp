#include <iostream>

class A {
 public:
  float a = 10.5;
};

class B: public A {
  public:
    int a = 7;
    int c = 10;
    const A& getA() {
      return *this;
    }
};

int main() {
  B b;
  std::cout << b.getA().a << std::endl;
}
