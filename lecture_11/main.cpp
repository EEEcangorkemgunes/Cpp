#include <iostream>

template <typename T>
class Triple {
 public:
  Triple(const T &a,const T &b,const T &c) : first(a), second(b), third(c) {}
  void Print() { std::cout << first << "\t" << second << "\t" << third << std::endl; }

 private:
  T first;
  T second;
  T third;
};
template <>
class Triple<std::string> {
 public:
  Triple(std::string a, std::string b, std::string c) : first(a), second(b), third(c) {}
  void Print() { std::cout << third << "\t" << second << "\t" << first << std::endl; }
 private:
  std::string first;
  std::string second;
  std::string third;
};

int main() {

  Triple t1(3, 4, 5);
  t1.Print();
  Triple t2(std::string{"Alice"}, std::string{"Bob"}, std::string{"Charlie"});
  t2.Print();

  return 0;
}