#include <iostream>

class Character {
 public:
  Character(){
    std::cout << "Creating Character\n";
  }
  ~Character(){
    std::cout << "Destroying Character\n";
  }
};

void SelectCharacter() {
  // A new stack frame is created for
  // SelectCharacter.  Local variable Frodo is
  // allocated on the stack
  Character Frodo;
  // When SelectCharacter ends, Frodo is
  // deallocated. Destructor is called as the
  // stack frame is removed
}

int main() {
  std::cout << "Program Starting\n";

  // Call SelectCharacter, creating and
  // destroying Frodo
  SelectCharacter();
  // After SelectCharacter returns, its stack 
  // frame is removed. Memory used by Frodo is freed
  std::cout << "Program Ending\n";
}