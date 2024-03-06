#include <iostream>
#include <vector>
#include <string>

std::vector<int> ZFunction(std::string &str) {
  int n = str.size();
  int left = 0;
  int right = 0;
  std::vector<int> z(n, 0);
  z[0] = n;

  for (int i = 1; i < n; ++i) {
    if (i < right) {
      z[i] = std::min(right - i, z[i - left]);
    }

    while (i + z[i] < n && str[z[i]] == str[i + z[i]]) {
      ++z[i];
    }

    if (i + z[i] > right) {
      left = i;
      right = i + z[i];
    }
  }

  return z;
}

int main() {
  std::string s;
  std::cin >> s;

  for (auto x : ZFunction(s)) {
    std::cout << x << " ";
  }

  return 0;
}