/*
önce registered account lar print olur, balance ları yazar
acc1 50 000
acc2 300 000
acc3 650 000

hemen ardına işlem sorulur
işlem? acc2 acc1 100000
işlem? acc3 acc1 150000

işlem yapısı şu şekilde: gönderici alıcı miktar
*/

#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <condition_variable>

class Account {
 public:
  Account() = default;
  Account(int b) : balance{b} {}

 public:
  void WithDraw(int amount) {
    while (amount--) {
      std::lock_guard<std::mutex> lock{balance_mutex};
      
      balance--;
      std::this_thread::sleep_for(std::chrono::microseconds(10));
      balance_mutex.unlock();
    }
  }
  void Deposit(int amount) {
    while (amount--) {
      balance_mutex.lock();
      balance++;
      std::this_thread::sleep_for(std::chrono::microseconds(10));
      balance_mutex.unlock();
    }
  }
  Account(Account&& other)
      : balance{other.balance} {}  // defined for std::unordered_map::emplace

  std::mutex balance_mutex;
  int balance;
};

class BankSystem {
 public:
  struct Transaction {
    std::string from;
    std::string to;
    int amount;
  };
  static std::string TransactionToStr(Transaction t) {
    std::string result =
        t.from + " ---" + std::to_string(t.amount) + "---> " + t.to;
    return result;
  }

  void CreateAccount(const std::string& name, int initial_balance) {
    accounts.emplace(name, Account{initial_balance});
  }

  void Transfer(const Transaction& t) {
    accounts[t.from].WithDraw(t.amount);
    accounts[t.to].Deposit(t.amount);
    std::cout << "##############################" << std::endl;
    std::cout << TransactionToStr(t) << std::endl;
    std::cout << "##############################" << std::endl;
  }

  std::unordered_map<std::string, Account> accounts;
};

class App {
 public:
  App() = default;
  App(BankSystem* b) : bank{b} {}
  ~App() {
    for (auto& t : transactions_in_progress)
      if (t.joinable()) t.join();
  }

  void Exec() {
    running = true;
    PrintInfo();

    while (running) {
      std::string input;
      std::getline(std::cin, input);

      if (input == "print") {
        PrintInfo();
        continue;
      }
      if (input == "exit") {
        running = false;
        continue;
      }

      ProcessInstruction(input);
    }
  }

  void PrintInfo() const {
    for (const auto& [name, acc] : bank->accounts)
      std::cout << name << ": " << acc.balance << std::endl;
  }

  void ProcessInstruction(const std::string& input) {
    std::istringstream iss{input};
    std::string from, to;
    int amount;

    iss >> from >> to >> amount;
    BankSystem::Transaction transaction{from, to, amount};
    // bank->Transfer(transaction);
    transactions_in_progress.emplace_back(&BankSystem::Transfer, bank,
                                          transaction);
  }

  bool running{false};
  BankSystem* bank;
  std::vector<std::thread> transactions_in_progress;
};

int main() {
  BankSystem b;

  b.CreateAccount("Selin", 50'000);
  b.CreateAccount("Ahmet", 300'000);
  b.CreateAccount("Hasan", 650'000);

  App app{&b};
  app.Exec();

  return 0;
}