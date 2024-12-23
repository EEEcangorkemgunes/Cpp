
#include <iostream>

/*
Normalde bir fonksiyonu tanımladığımızda program'ın çalıştığı süre boyunca
bellekte bir yer kaplar. Fakat bazen programın çalıştığı süre boyunca bellekte
yer kaplamasını istemeyebiliriz. Bu durumda lambda fonksiyonları devreye girer.
Lambda fonksiyonları, programın çalıştığı süre boyunca bellekte yer kaplamazlar.

Lambda fonksiyonları auto anahtar kelimesi ile tanımlanır. Lambda fonksiyonları
bir fonksiyon gibi çağrılabilirler. Lambda fonksiyonları bir fonksiyon gibi
parametre alabilirler. Lambda fonksiyonları bir fonksiyon gibi bir değer
döndürebilirler.
*/

/*
default olarak lambda fonksiyon tanımlaması aşağıdaki gibidir.
*/
auto lambda1 = []() {
    std::cout << "Hello World!" << std::endl;
    return 5;
};

/*
Bu şekilde tanımlayarak lambda fonksiyonlarının dönüş tipi de belirlenebilir.

*/
auto lambda2 = []() -> int {
    std::cout << "Hello World!" << std::endl;
    return 5;
};

/*



*/

auto lambda3 = [&]() {
    std::cout << "Hello World!" << std::endl;
    return 5;
};

/*



*/
auto lambda4 = [](int x, int y) {
    std::cout << "Hello World!" << std::endl;
    return x + y;
};

int main() {
    int x = 1;
    int y = 3;

    auto lambda5 = [x, y]() { return x + y; };

    auto lambda6 = [&x, &y]() { return x + y; };

    auto lambda7 = [=]() { return x + y; };

    auto lambda8 = [&]() { return x + y; };

    return 0;
}