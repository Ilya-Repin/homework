#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefFunc(std::string &s) {
  int n = s.size();
  std::vector<int> p(n, 0);

  for (int i = 1; i < n; ++i) {
    int k = p[i - 1];

    while (k > 0 && s[k] != s[i]) {
      k = p[k - 1];
    }

    if (s[i] == s[k]) {
      p[i] = k + 1;
    }
  }

  return p;
}

int main() {
  std::string s;
  std::cin >> s;

  for (auto x : PrefFunc(s)) {
    std::cout << x << " ";
  }

  return 0;
}