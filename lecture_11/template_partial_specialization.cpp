#include <iostream>

template <typename T, typename U, typename V>
class Triple {
 public:
  Triple(T a, U b, V c) : first(a), second(b), third(c) {}
  void Print() { std::cout << first << "\t" << second << "\t" << third << std::endl; }

 private:
  T first;
  U second;
  V third;
};

template <typename T, typename U>
class Triple<T, U, std::string> {
 public:
  Triple(T a, U b, std::string c) : first(a), second(b), third(c) {}
  void Print() { std::cout << third << "\t" << second << "\t" << first << std::endl; }

 private:
  T first;
  U second;
  std::string third;
};
template <typename T, typename U>
class Triple<int, T, U> {
 public:
  Triple(int a, T b, U c) : first(a), second(b), third(c) {}
  void Print() { std::cout << third << "\t" << second << "\t" << first << std::endl; }

 private:
  int first;
  T second;
  U third;
};

int main() {
  Triple t1(3, 4, 5);
  t1.Print();
  Triple t2(3, 4, std::string{"Charlie"});
  t2.Print();
  Triple t3(std::string{"Alice"}, std::string{"Bob"}, 5);
  t3.Print();

  return 0;
}