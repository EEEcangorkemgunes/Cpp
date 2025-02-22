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

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <thread>
#include <chrono>

class Account{
    public:
    Account() = default;
    Account(int b) : balance{b} {}
    public:
    void WithDraw(int amount){
        while(amount--){
            balance --;
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    }
    void Deposit(int amount){
        while(amount--){
            balance ++;
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    }

    int balance;
};

class BankSystem{
    public:
    struct Transaction{
        std::string from;
        std::string to;
        int amount;
    };
    static std::string TransactionToStr(Transaction t){
        std::string result = t.from + " ---" + std::to_string(t.amount) + "---> " + t.to;
        return result;
    }

    void RegisterUsers(const std::string& name, const Account& acc) {
        accounts[name] = acc;
    }

    void Transfer(const Transaction& t){
        accounts[t.from].WithDraw(t.amount);
        accounts[t.to].Deposit(t.amount);
        std::cout << "##############################" << std::endl;
        std::cout << TransactionToStr(t) << std::endl;
        std::cout << "##############################" << std::endl;
    }

    std::unordered_map<std::string, Account> accounts;
};

class App{
    public:
    App() = default;
    App(BankSystem* b) : bank{b} {

    }

    void Exec() {
        while(true) {
            PrintInfo();
            GetTransactionInfo();
        }
    }

    void PrintInfo() const{
        for(const auto& [name, acc] : bank->accounts)
            std::cout << name << ": " << acc.balance << std::endl;
    }

    void GetTransactionInfo() {
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss{input};
        
        std::string from, to;
        int amount;
        
        iss >> from >> to >> amount;
        BankSystem::Transaction transaction{from, to, amount};
        bank->Transfer(transaction);
    }

    BankSystem* bank;
};


int main(){
    BankSystem b;
    b.RegisterUsers("Selin", Account{50'000});
    b.RegisterUsers("Ahmet", Account{300'000});
    b.RegisterUsers("Hasan", Account{650'000});

    App app{&b};
    app.Exec();

    return 0;
}