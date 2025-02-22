#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <mutex> // Include the mutex header for std::once_flag and std::call_once

class BankAccount {
 public:
  void printBalance() const {
    // Implementation of printBalance
  }
};

class Menu {
 public:
  static void printMenu() {
    std::cout << "Welcome to Cihan Can Bank" << std::endl;
    std::cout << "Please write your instructions:" << std::endl;
  }
};

class Application {
 public:
  void exec() {
    std::call_once(flag, [&]() {
      std::string instruction;
      Menu::printMenu();
      std::getline(std::cin, instruction);
      while (instruction != "exit") {
        std::istringstream iss(instruction);
        std::string word;
        // Process the instruction
        std::getline(std::cin, instruction);
      }
    });
  }

 private:
  std::unordered_map<std::string, BankAccount> accounts;
  std::once_flag flag; // Add a once_flag to ensure exec is only called once
};

int main() {
  Application app;
  app.exec();
  return 0;
}