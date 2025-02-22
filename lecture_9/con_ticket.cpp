#include <algorithm>
#include <iostream>
#include <set>
int main() {
  int n, m;
  std::multiset<int> t;

  std::cin >> n >> m;
  int temp;
  for (int i = 0; i < n; ++i) {
    std::cin >> temp;
    t.insert(temp);
  }
  for (int i = 0; i < m; ++i) {
    int temp;
    std::cin >> temp;
    auto it = t.upper_bound(temp);

    if (it != t.begin()) {
      it--;
    }
    if (*it > temp) {
      std::cout << -1 << '\n';
    } else {
      std::cout << *it << '\n';
      t.erase(it);
    }
  }
}
