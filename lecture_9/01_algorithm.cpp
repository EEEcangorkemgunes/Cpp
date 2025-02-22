#include <iostream>
#include <algorithm>
#include <vector>

int main(){
  int no_of_tickets, no_of_customers, price;
  std::vector<int> ticket_prices;
  std::cin >> no_of_tickets >> no_of_customers;
  for(int i = 0; i < no_of_tickets; i++){
    std::cin >> ticket_prices.emplace_back();
  }
  for(auto it = ticket_prices.begin(); it != ticket_prices.end(); it++){
    std::cout << *it << " ";
  }

}