#include <iostream>
#include <memory>
int main(){
  auto SharedPtr{std::make_shared<int>(42)};
  int* RawPtr{SharedPtr.get()};
  if (RawPtr) {
    std::cout << "RawPtr is truthy | Value: "
      << *RawPtr << "addr: " << RawPtr;
  }

  SharedPtr.reset();

  if (RawPtr) {
    std::cout << "\nStill truthy | Value: "
      << *RawPtr;
  }
}