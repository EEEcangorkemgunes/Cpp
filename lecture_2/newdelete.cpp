#include <iostream>

class Car {
   public:
    Car() { std::cout << "default car " << std::endl; }
    Car(std::string b) : brand{b} { std::cout << "branded car " << std::endl; }

    std::string brand;
};

int main() {
    double* d_p = new double;
    std::cout << "d_p: " << *d_p << std::endl;
    delete d_p;

    double* d_p2 = new double{5.2};
    std::cout << "d_p: " << *d_p2 << std::endl;
    delete d_p2;

    std::string* str_p = new std::string{"ahmet"};
    std::cout << "d_p: " << *str_p << std::endl;
    delete str_p;

    Car* c_p = new Car;  // Car c;
    delete c_p;
    Car* c_p2 = new Car{"bmw"};  // Car c2{"bmw"};
    delete c_p2;

    Car* car_arr = new Car[3];
    Car* car_arr2 = new Car[3]{{"bmw"}, {"merce"}, {"fiat"}};
    delete[] car_arr;
    delete[] car_arr2;

    return 0;
}