#include <iostream>
#include <string>

class Vehicle {
   public:
    Vehicle() { std::cout << "Vehicle created" << std::endl; }
    Vehicle(const Vehicle& a) { std::cout << "Vehicle copied" << std::endl; }
    std::string brand;
};

void func1(Vehicle obj) {}   // pass by value
void func2(Vehicle* obj) {}  // pass by pointer
void func3(Vehicle& obj) {}  // pass by reference
void func4(Vehicle* obj) {}  // pass by pointer
void func5(Vehicle& obj) {   //It will change the original object
    obj.brand = "Toyota";
}

int main() {
    // Vehicle v1 created
    Vehicle v1;
    v1.brand = "Ford";
    // Vehicle copied (copy constructor called)
    func1(v1);
    std::cout << "----------------" << std::endl;
    // No copy, original object is passed
    func2(&v1);
    std::cout << "----------------" << std::endl;
    func3(v1);  // Pass object directly
    std::cout << "----------------" << std::endl;
    func4(&v1);  // Pass object address
    std::cout << "----------------" << std::endl;
    func5(v1);  // Pass object reference
    std::cout << "brand: " << v1.brand << std::endl;
    std::cout << "----------------" << std::endl;

    return 0;
}
