 #include <iostream>
#include <vector>
#include <algorithm>
class A {
 public:
  A() = delete;
  A(int val, std::string name) : _a{val}, _name{name} { std::cout << "Object created!" << std::endl; }
  A(const A &a) : _a{a._a}, _name{a._name} { std::cout << "Copy constructor" << std::endl; }
  A(A &&a) : _a{std::move(a._a)}, _name{std::move(a._name)} { std::cout << "Move constructor" << std::endl; }
  void PrintInfo() { std::cout << _name << " " << _a << std::endl; }
  int GetA() const { return _a; }
  void SetA(int val) { _a = val; }
  void SetName(std::string name) { _name = name; }
  std::string GetName() const { return _name; }
  bool operator<(const A &a) const {
    if (_a == a._a) {
      return _name < a._name;
    }
    return _a < a._a;
  }
  A &operator=(const A &a) {
    std::cout << "Copy assignment" << std::endl;
    _a = a._a;
    _name = a._name;
    return *this;
  }
  A &operator=(A &&a) {
    std::cout << "Move assignment" << std::endl;
    _a = std::move(a._a);
    _name = std::move(a._name);
    return *this;
  }

 private:
  int _a;
  std::string _name;
};

class B {
 public:
  B() = delete;
  B(int val, std::string name) : _a{new int(val)}, _name{name} { std::cout << "Object created!" << std::endl; }
  B(const B &other) : _a{new int(*other._a)}, _name{other._name} { std::cout << "Copy constructor" << std::endl; }
  B(B &&other) : _a{std::move(other._a)}, _name{std::move(other._name)} {
    other._a = nullptr;
    std::cout << "Move constructor" << std::endl;
  }
  ~B() { std::cout << "Object destroyed!" << std::endl; }
  void PrintInfo() {
    std::cout << "name:" << _name << " " << std::endl;
    if (_a == nullptr) {
      std::cout << "a is null";
    } else {
      std::cout << *_a;
    }
  }
  int GetA() const { return *_a; }
  void SetA(int val) { *_a = val; }
  void SetName(std::string name) { _name = name; }
  std::string GetName() const { return _name; }
  bool operator<(const B &a) const {
    if (_a == a._a) {
      return _name < a._name;
    }
    return _a < a._a;
  }
  B &operator=(const B &a) {
    std::cout << "Copy assignment" << std::endl;
    _a = a._a;
    _name = a._name;
    return *this;
  }
  B &operator=(B &&a) {
    std::cout << "Move assignment" << std::endl;
    _a = std::move(a._a);
    _name = std::move(a._name);
    return *this;
  }

 private:
  int *_a;
  std::string _name;
};
// sort using lambda function
//  int main() {
//    std::vector<A> members;
//    members.emplace_back(2, "Alice");
//    members.emplace_back(1, "Bob");
//    members.emplace_back(4, "Diana");
//    members.emplace_back(3, "Eve");
//    members.emplace_back(5, "Charlie");
//    members.emplace_back(6, "Charlie");
//    members.emplace_back(2, "Charlie");
//    members.emplace_back(5, "Bob");
//    for (auto &member : members) {
//      member.PrintInfo();
//    }
//    std::cout << "After sorting" << std::endl;
//    std::sort(members.begin(), members.end(),[](const A &a, const A &b){
//      if (a.GetA() == b.GetA()) {
//        return a.GetName() < b.GetName();
//      }
//      return a.GetA() < b.GetA();
//    });
//    for (auto &member : members) {
//      member.PrintInfo();
//    }
//    return 0;
//  }

// sort using operator overload
// int main() {
//   std::vector<A> members;
//   members.emplace_back(2, "Alice");
//   members.emplace_back(1, "Bob");
//   members.emplace_back(4, "Diana");
//   members.emplace_back(3, "Eve");
//   members.emplace_back(5, "Charlie");
//   members.emplace_back(6, "Charlie");
//   members.emplace_back(2, "Charlie");
//   members.emplace_back(5, "Bob");
//   for (auto &member : members) {
//     member.PrintInfo();
//   }
//   std::cout << "After sorting" << std::endl;
//   std::sort(members.begin(), members.end());
//   for (auto &member : members) {
//     member.PrintInfo();
//   }
//   return 0;
// }

// std::pair default olarak first'e göre sıralar. Farklı bir sıralama istiyorsak lambda fonksiyonu kullanarak sıralama yapabiliriz.
// int main() {
//   std::vector<std::pair<std::string, A>> members;
//   members.emplace_back("member7", A(2, "Charlie"));
//   members.emplace_back("member2", A(1, "Bob"));
//   members.emplace_back("member1", A(2, "Alice"));
//   members.emplace_back("member3", A(4, "Diana"));
//   members.emplace_back("member4", A(3, "Eve"));
//   members.emplace_back("member9", A(7, "Frank"));
//   members.emplace_back("member6", A(6, "Charlie"));
//   members.emplace_back("member5", A(5, "Charlie"));
//   members.emplace_back("member10", A(8, "Grace"));
//   members.emplace_back("member8", A(5, "Bob"));
//   std::sort(members.begin(), members.end(), [](const std::pair<std::string, A> &a, const std::pair<std::string, A> &b) {
//     if (a.second.GetName() == b.second.GetName()) {
//       return a.first < b.first;
//     }
//     return a.second.GetName() < b.second.GetName();
//   });
//   for (auto &member : members) {
//     std::cout << member.first << " ";
//     member.second.PrintInfo();
//   }
//   return 0;
// }

// std::for_each kullanımı
// int main() {
//   std::vector<A> members;
//   int sum = 0;
//   members.emplace_back(2, "Alice");
//   members.emplace_back(1, "Bob");
//   members.emplace_back(4, "Diana");
//   members.emplace_back(3, "Eve");
//   members.emplace_back(5, "Charlie");
//   members.emplace_back(6, "Charlie");
//   members.emplace_back(2, "Charlie");
//   members.emplace_back(5, "Bob");
//   std::for_each(members.begin(), members.end(),[&sum](A &a){
//     sum += a.GetA();
//     a.SetA(a.GetA() * a.GetA());
//   });
//   std::cout << "Sum: " << sum << std::endl;
//   for (auto &member : members) {
//     member.PrintInfo();
//   }
//   return 0;
// }

// int main() {
//   std::vector<A> members;
//   members.reserve(10);
//   int sum = 0;
//   // members.push_back(A(2, "Alice"));
//   members.emplace_back(2, "Alice");
//   members.emplace_back(1, "Bob");
//   members.emplace_back(4, "Diana");
//   members.emplace_back(3, "Eve");
//   members.emplace_back(5, "Charlie");
//   members.emplace_back(6, "Charlie");
//   members.emplace_back(2, "Charlie");
//   members.emplace_back(5, "Bob");
//   std::vector<A> new_members;
//   new_members.reserve(10);
//   // new_members = members;
//   int i = 0;
//   for (auto it = members.begin(); it != members.end(); it++) {
//     new_members.emplace_back(std::move(*it));
//   }
//   std::cout << "------------------" << std::endl;
//   for (auto &member : members) {
//     member.PrintInfo();
//   }
//   return 0;
// }

// int main() {
//   std::vector<B> members;
//   members.reserve(10);
//   int sum = 0;
//   // members.push_back(A(2, "Alice"));
//   members.emplace_back(2, "Alice");
//   members.emplace_back(1, "Bob");
//   members.emplace_back(4, "Diana");
//   members.emplace_back(3, "Eve");
//   members.emplace_back(5, "Charlie");
//   members.emplace_back(6, "Charlie");
//   members.emplace_back(2, "Charlie");
//   members.emplace_back(5, "Bob");
//   std::vector<B> new_members;
//   new_members.reserve(10);
//   // new_members = members;
//   int i = 0;
//   for (auto it = members.begin(); it != members.end(); it++) {
//     new_members.emplace_back(std::move(*it));
//   }
//   std::cout << "------------------" << std::endl;
//   for (auto &member : members) {
//     member.PrintInfo();
//   }
//   return 0;
// }

int main() {
  std::vector<A> members;
  std::vector<A> new_members;
  members.reserve(10);
  new_members.reserve(10);
  members.emplace_back(2, "Alice");
  members.emplace_back(1, "Bob");
  members.emplace_back(4, "Diana");
  members.emplace_back(3, "Eve");
  members.emplace_back(5, "Charlie");
  members.emplace_back(6, "Charlie");
  members.emplace_back(2, "Charlie");
  members.emplace_back(5, "Bob");
  std::copy(members.begin(), members.end(), new_members.begin());
  // for(auto &member : members){
  //   new_members.emplace_back(member);
  // }
  std::cout << "------------------" << std::endl;
  for (auto &member : new_members) {
    member.PrintInfo();
  }
  return 0;
}