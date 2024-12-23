#include <iostream>
#include <thread>
void hello() { std::cout << "Hello World!" << std::endl; }
int main() {
  void (*f)() = hello;

  std::thread t1(hello);
  // std::thread t2(f);
  // std::thread t3([]() { std::cout << "Hello World!" << std::endl; });
  t1.detach();
  // t1.join();

  // t2.join();
  // for (int i = 0; i < 10; i++) {
  //   std::cout << "Main thread" << std::endl;
  // }
  // t3.join();
  return 0;
}
