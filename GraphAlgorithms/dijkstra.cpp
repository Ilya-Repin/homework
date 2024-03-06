#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Pair {
 public:
  int vertex;
  int weight;

  Pair(int v, int w) : vertex(v), weight(w) {
  }

  bool operator<(const Pair &other) const {
    return weight > other.weight;
  }
};

struct Edge {
 public:
  int to;
  int weight;

  Edge(int v, int w) : to(v), weight(w) {
  }
};

class Graph {
 private:
  std::vector<std::vector<Edge>> edges_;
  std::vector<int> dist_;

 public:
  explicit Graph(int n) : edges_(n), dist_(n, std::numeric_limits<int>::max()) {
  }

  std::vector<int> FindShortestWays(int start) {
    std::priority_queue<Pair> pq;
    pq.emplace(start, 0);
    dist_[start] = 0;

    while (!pq.empty()) {
      int v = pq.top().vertex;
      int w = pq.top().weight;
      pq.pop();

      if (dist_[v] < w) {
        continue;
      }

      for (auto edge : edges_[v]) {
        auto u = edge.to;
        auto weight = edge.weight;
        if (dist_[u] > dist_[v] + weight) {
          dist_[u] = dist_[v] + weight;
          pq.emplace(u, dist_[v] + weight);
        }
      }
    }

    return dist_;
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int u, v, w;
  is >> u >> v >> w;

  g.edges_[u].emplace_back(v, w);
  g.edges_[v].emplace_back(u, w);

  return is;
}

int main() {
  int k;
  std::cin >> k;

  for (int i = 0; i < k; i++) {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);

    for (int j = 0; j < m; j++) {
      std::cin >> g;
    }

    int start;
    std::cin >> start;

    std::vector<int> dist = g.FindShortestWays(start);

    for (int j = 0; j < n; j++) {
      if (dist[j] == std::numeric_limits<int>::max()) {
        std::cout << "2009000999 ";
      } else {
        std::cout << dist[j] << " ";
      }
    }

    std::cout << '\n';
  }

  return 0;
}