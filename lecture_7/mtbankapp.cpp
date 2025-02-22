
#include <array>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

class BankAccount {
 public:
  BankAccount() = default;
  BankAccount(std::string n, int amount) : name(n), balance(amount) {}
  void deposit(int amount) {
    while (amount--) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      balance++;
    }
  }
  void withdraw(int amount) {
    while (amount--) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      balance--;
    }
  }
  int getBalance() { return balance; }
  void printBalance() { std::cout << name << " has " << balance << std::endl; }

 private:
  std::string name;
  int balance;
};
//mutex'in
// struct Transaction {
//   BankAccount& from;
//   BankAccount& to;
//   int amount;
// };

class Transaction {
 public:
  static bool transfer(BankAccount& from, BankAccount& to, int amount) {
    if (from.getBalance() < amount) {
      return false;
    }
    from.withdraw(amount);
    to.deposit(amount);
    return true;
  }
};
class Menu {
 public:
  static void printMenu() {
    std::cout << "Welcome to Cihan Can Bank" << std::endl;
    std::cout << "Please write your instructions:" << std::endl;
  }
};
enum TransactionError {

};

// enum Instruction { DEPOSIT, WITHDRAW, TRANSFER, EXIT, INVALID };

enum InstructionError {
  NO_ERROR,
  INVALID_AMOUNT,
  INVALID_ACCOUNT,
  INVALID_NUMBER_OF_ARGUMENTS
};

class InstructionParser {
 public:
  static InstructionError parse(std::string instruction,
                                std::array<std::string, 3>& words) {
    std::istringstream iss(instruction);
    std::string word;
    int i = 0;

    while (iss >> word) {
      if (i > 2) {
        return InstructionError::INVALID_NUMBER_OF_ARGUMENTS;
      }
      words[i++] = word;
    }
    if (i != 3) {
      return InstructionError::INVALID_NUMBER_OF_ARGUMENTS;
    }
    return InstructionError::NO_ERROR;
  }
};

class Application {
 public:
  void exec() {
    accounts["Ali"] = BankAccount("Ali", 100000);
    accounts["Veli"] = BankAccount("Veli", 200000);
    accounts["Deli"] = BankAccount("Deli", 300000);
    std::string instruction;
    int instructionError = InstructionError::NO_ERROR;
    printBalances();
    Menu::printMenu();
    std::getline(std::cin, instruction);
    std::vector<std::thread> threads;
    while (instruction != "exit") {
      if (instruction == "print") {
        printBalances();
        std::getline(std::cin, instruction);
        continue;
      }

      std::istringstream iss(instruction);
      std::string word;
      std::array<std::string, 3> words;
      int i = 0;

      while (iss >> word) {
        if (i > 2) {
          std::cout << "Invalid instruction" << std::endl;
          break;
        }
        words[i++] = word;
      }
      if (i != 3) {
        std::cout << "Invalid instruction" << std::endl;
        Menu::printMenu();
        std::getline(std::cin, instruction);
        continue;
      }
      threads.emplace_back(
          std::thread(Transaction::transfer, std::ref(accounts[words[0]]),
                      std::ref(accounts[words[1]]), std::stoi(words[2])));
      printBalances();
      Menu::printMenu();
      std::getline(std::cin, instruction);
    }
    for (auto& thread : threads) {
      thread.join();
    }
  }

 private:
  std::unordered_map<std::string, BankAccount> accounts;
  void printBalances() {
    for (auto& account : accounts) {
      account.second.printBalance();
    }
  }
};

int main() {
  Application app;
  app.exec();

  return 0;
}