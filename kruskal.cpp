#include <iostream>
#include <vector>

class CDS {
 private:
  std::vector<int> p_;
  std::vector<int> rank_;

 public:
  explicit CDS(size_t n) : rank_(n, 0) {
    for (size_t i = 0; i < n; ++i) {
      p_.push_back(i);
    }
  }

  int FindSet(int x) {
    if (p_[x] == x) {
      return x;
    }

    return p_[x] = FindSet(p_[x]);
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (rank_[x] < rank_[y]) {
      p_[x] = y;
    } else if (rank_[x] > rank_[y]) {
      p_[y] = x;
    } else {
      p_[x] = y;
      rank_[y] += 1;
    }
  }
};

struct Edge {
  double weight;
  int first;
  int second;

  bool operator<(const Edge &other) const {
    return weight < other.weight;
  }
};

class Graph {
 private:
  std::vector<Edge> edges_;
  std::vector<Edge> mst_;
  int amount_;

 public:
  explicit Graph(int n) : amount_(n) {
  }

  void FindMST() {
    CDS cds(amount_);

    for (auto edge : edges_) {
      if (cds.FindSet(edge.first) != cds.FindSet(edge.second)) {
        cds.Union(edge.first, edge.second);
        mst_.push_back(edge);
      }
    }

    int sum = 0;
    for (auto x : mst_) {
      sum += x.weight;
    }

    std::cout << sum;
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);
};

std::istream &operator>>(std::istream &is, Graph &g) {
  std::ios_base::sync_with_stdio(false);
  int u, v, w;
  is >> u >> v >> w;
  --u;
  --v;

  Edge new_edge;
  new_edge.weight = w;
  new_edge.first = u;
  new_edge.second = v;
  g.edges_.push_back(new_edge);

  return is;
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.FindMST();

  return 0;
}