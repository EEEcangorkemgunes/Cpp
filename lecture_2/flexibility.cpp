#include <iostream>

class Character {
 public:
  Character() { std::cout << "Creating Character\n"; }
  ~Character() { std::cout << "Destroying Character\n"; }
  Character(const Character& other) {
    std::cout << "Copying Character\n";
    Name = other.Name;
  }
  Character(Character&& other) {
    std::cout << "Moving Character\n";
    Name = "name yok";
  }
  Character& operator=(Character&& other) {
    std::cout << "Moving Character Overload\n";
    Name = other.Name;
    return *this;
  }
  std::string Name{"Frodo"};
};

Character SelectCharacter() {
  Character Frodo;
  return Frodo;
}

int main() {
  Character SelectedCharacter{SelectCharacter()};
  std::cout << "Getting Character Name:\n";
  std::cout << SelectedCharacter.Name << std::endl;
}