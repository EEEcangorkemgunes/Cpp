#include <cstring>
#include <iostream>
using namespace std;

class MyString {
  char* data;

 public:
  MyString(const char* str) {
    data = new char[strlen(str) + 1];
    strcpy(data, str);
  }

  ~MyString() { delete[] data; }
  MyString(const MyString& str) {
    data = new char[strlen(str.data) + 1];
    strcpy(data, str.data);
  }

  // No move constructor is defined!
};

void testMove(MyString str) {  // Expects a temporary object to move.
  cout << "Function testMove executed" << endl;
}

int main() {
  MyString s1("Hello");
  testMove(std::move(s1));  // Error: No move constructor!
  int a = 10;
  return 0;
}
