#include <iostream>
#include <memory>   // for smart ptrs

/* class MyInt{
    public:
    MyInt() {  my_resource = new int; }
    MyInt(int val) { my_resource = new int{val}; }
    ~MyInt() { delete my_resource; }

    int* my_resource;
};

int main() {

    {
        MyInt number{23};   // constructor invoke
        std::cout << *(number.my_resource) << std::endl;
    }   // desctructor invoke

    {
        int* p = new int{11};
        std::cout << *p << std::endl;
    }


    return 0;
} */

//////////////////////////////// UNIQUE PTR
// single ownership
// custom destrouctor hangi case 'de kullanılıyor?

class Car{
    public:
    Car() {  std::cout << "default car " << std::endl; }
    Car(std::string b) : brand{b} { std::cout << "branded car " << std::endl;}
    ~Car() { /* do whatever you need */}

    std::string brand;
};

/* int main(){
    //double* d_p = new double;
    std::unique_ptr<double> d_p = std::make_unique<double>();
    std::unique_ptr<double> d_p2 = std::make_unique<double>(26.5);
    std::cout << *d_p2 << std::endl;

    std::unique_ptr<Car> c_p = std::make_unique<Car>("BMW");
    std::cout << c_p->brand << std::endl;

    // std::unique_ptr<Car> c_p2 = c_p; // no multiple ownership possible
    std::unique_ptr<Car> c_p2;
    c_p2 = std::move(c_p);
    if(c_p)
        std::cout << "c_p has resource" << std::endl;
    else
        std::cout << "c_p has no resource" << std::endl;

    std::cout << "c_p2 has " << c_p2->brand << std::endl;

    c_p2.release();
    std::cout << "after c_p2 release:" << std::endl;
    if(c_p2)
        std::cout << "c_p2 has resource" << std::endl;
    else
        std::cout << "c_p2 has no resource" << std::endl;

    c_p2 = std::make_unique<Car>("BMW");
    c_p2.reset(new Car{"FIAT"});
    std::cout << c_p2->brand << std::endl;
} */

//////////////////////////////// SHARED PTR
// multiple ownership

/* int main(){
    std::shared_ptr<int> i_p = std::make_shared<int>(6);
    std::cout << *i_p << std::endl;
    {
        std::shared_ptr<int> i_p2{i_p}; // i_p2 has the ownership of the resource owned by i_p
        std::cout << *i_p2 << std::endl;
    }   // does not free the resource (6) since i_p still exits and has the ownership of the rescource
    std::cout << *i_p << std::endl;

    std::cout << "owners: " << i_p.use_count() << std::endl;
    std::shared_ptr<int> i_p3 = std::make_shared<int>(3);

    i_p.swap(i_p3);
    std::cout << *i_p << std::endl;
    std::cout << *i_p3 << std::endl;
} */

