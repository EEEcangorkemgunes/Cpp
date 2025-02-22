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
#include <vector>

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
    ~App(){
        for(auto& t : transactions_in_progress)
            if(t.joinable())
                t.join();
    }

    void Exec() {
        running = true;
        while(running) {
            // PrintInfo();
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
        if(input == "print"){
            PrintInfo();
            return;
        }
        if(input == "exit"){
            running = false;
            return;
        }
        std::istringstream iss{input};
        
        std::string from, to;
        int amount;
        
        iss >> from >> to >> amount;
        BankSystem::Transaction transaction{from, to, amount};
        // bank->Transfer(transaction);
        transactions_in_progress.emplace_back(&BankSystem::Transfer, bank, transaction);
    }

    bool running{false};
    BankSystem* bank;
    std::vector<std::thread> transactions_in_progress;
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