#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Pair {
  int vertex = 0;
  int weight = 0;

  Pair(int v, int w) {
    vertex = v;
    weight = w;
  }

  bool operator<(const Pair &other) const {
    return (weight == other.weight ? vertex > other.vertex : weight > other.weight);
  }
};

struct Edge {
  int to = 0;
  int weight = 0;

  Edge(int v, int w) {
    to = v;
    weight = w;
  }
};

class Graph {
 private:
  std::vector<std::vector<Edge>> edges_;
  std::vector<Edge> mst_;
  int amount_ = 0;

 public:
  explicit Graph(int n) : edges_(n, std::vector<Edge>()), amount_(n) {
  }

  void FindMST() {
    std::vector<int> dist(amount_, std::numeric_limits<int>::max());
    std::vector<bool> visited(amount_, false);
    std::vector<int> prev(amount_, -1);
    std::priority_queue<Pair> heap;

    dist[0] = 0;
    heap.push(Pair(0, 0));

    while (!heap.empty()) {
      int v = heap.top().vertex;
      heap.pop();
      visited[v] = true;

      if (prev[v] != -1) {
        mst_.emplace_back(prev[v], v);
      }

      for (auto &neighbour : edges_[v]) {
        if (!visited[neighbour.to] && neighbour.weight < dist[neighbour.to]) {
          prev[neighbour.to] = v;
          dist[neighbour.to] = neighbour.weight;
          heap.emplace(Pair(neighbour.to, neighbour.weight));
        }
      }
    }

    int sum = 0;

    for (int d : dist) {
      sum += (d != std::numeric_limits<int>::max() ? d : 0);
    }

    std::cout << sum;
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int u, v, w;
  is >> u >> v >> w;
  --u;
  --v;
  g.edges_[u].emplace_back(v, w);
  g.edges_[v].emplace_back(u, w);

  return is;
}

int main() {
  int n, m;
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  std::cin >> n >> m;
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.FindMST();

  return 0;
}