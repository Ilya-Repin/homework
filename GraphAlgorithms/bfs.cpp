#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>
#include <queue>

class Graph {
 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> dist_;
  std::vector<int> parents_;

 public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    parents_ = std::vector<int>(n, -1);
  }

  int BFSVisit(int start, int end) {
    --start;
    std::queue<int> queue;
    queue.push(start);
    dist_[start] = 0;

    while (!queue.empty()) {
      int curr = queue.front();
      queue.pop();

      for (auto neighbour : vertexes_[curr]) {
        if (dist_[neighbour] >= dist_[curr] + 1) {
          dist_[neighbour] = dist_[curr] + 1;
          parents_[neighbour] = curr;
          queue.push(neighbour);
        }
      }
    }

    return dist_[end - 1] == std::numeric_limits<int>::max() ? -1 : dist_[end - 1];
  }

  int &GetParent(int son) {
    return parents_[son];
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].insert(end);
  g.vertexes_[end].insert(begin);

  return is;
}

int main() {
  int n, m, a, b;
  std::cin >> n >> m >> a >> b;
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  int l = g.BFSVisit(a, b);

  std::cout << l << "\n";
  if (l != -1) {
    std::vector<int> path;
    for (auto x = b - 1; x != -1; x = g.GetParent(x)) {
      path.push_back(x);
    }

    for (int i = path.size() - 1; i >= 0; --i) {
      std::cout << path[i] + 1 << " ";
    }
  }

  return 0;
}