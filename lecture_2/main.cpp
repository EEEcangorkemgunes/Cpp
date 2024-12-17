
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>


bool MultiplyByTwo(std::unique_ptr<double>& val){
  *val *= 2;
  if(val){
    return true;
  }
  return false;
}
bool MultiplyByTwo(double *val){
  *val *= 2;
  if(val){
    return true;
  }
  return false;
}
double FixHundred(std::unique_ptr<double> ptr){
  
  *ptr = 100;
  return *ptr;

}

int AddTwo(std::shared_ptr<int> val){
  *val += 2;
  std::cout << "owners: " << val.use_count() << std::endl;
  return *val;
}


int main(){
    std::unique_ptr<double> my_double_ptr = std::make_unique<double>(25.7);
    MultiplyByTwo(my_double_ptr);
    std::cout << *my_double_ptr << std::endl;
    std::cout << "-----------------" << std::endl;
    MultiplyByTwo(my_double_ptr.get());
    std::cout << *my_double_ptr << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << FixHundred(std::move(my_double_ptr)) << std::endl; // move ownership and my_double_ptr is released
    std::cout << "-----------------" << std::endl;
    std::shared_ptr<int> my_int_ptr =  std::make_shared<int>(15);
    std::cout << *my_int_ptr << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << AddTwo(my_int_ptr) << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << my_int_ptr.use_count() << std::endl;


  return 0;
}