
#include <array>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

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

struct Transaction {
  BankAccount& from;
  BankAccount& to;
  int amount;
};

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

class Application {};

int main() {
  std::unordered_map<std::string, BankAccount> accounts{
      {"ahmet", BankAccount("ahmet", 100000)},
      {"ali", BankAccount("ali", 150000)},
      {"veli", BankAccount("veli", 250000)}};
  std::string instruction;
  int i = 0;

  for (auto& account : accounts) {
    account.second.printBalance();
  }
  Menu::printMenu();
  std::getline(std::cin, instruction);
  while (instruction != "exit") {
    std::istringstream iss(instruction);

    std::string word;
    std::array<std::string, 3> words;
    i = 0;
    while (iss >> word) {
      words[i++] = word;
    }
    Transaction t(accounts[0], accounts[1]);
    Transaction::transfer(accounts[words[0]], accounts[words[1]],
                          std::stoi(words[2]));
    for (auto& account : accounts) {
      account.second.printBalance();
    }
    Menu::printMenu();
    std::getline(std::cin, instruction);
  }

  return 0;
}