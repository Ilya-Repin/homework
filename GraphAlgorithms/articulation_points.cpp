#include <iostream>
#include <vector>
#include <set>

struct Vertex {
  int index = 0;
  int time_in = 0;
  int time_up = 0;
  bool visited = false;

  explicit Vertex(int i) : index(i) {
  }
};

class Graph {
 private:
  int time_ = 0;
  std::vector<Vertex> vertexes_;
  std::vector<std::vector<int>> edges_;
  std::set<int> articulation_points_;

 public:
  explicit Graph(int n) {
    edges_ = std::vector<std::vector<int>>(n);

    for (int i = 0; i < n; ++i) {
      vertexes_.emplace_back(i);
    }
  }

  std::vector<Vertex> &GetVertexes() {
    return vertexes_;
  }

  std::set<int> &GetArticulationPoints() {
    return articulation_points_;
  }

  void Dfs(Vertex &v, bool is_root) {
    v.visited = true;
    v.time_in = v.time_up = ++time_;

    int children = 0;

    for (auto &neighbour : edges_[v.index]) {
      if (vertexes_[neighbour].visited) {
        v.time_up = std::min(v.time_up, vertexes_[neighbour].time_in);
      } else {
        ++children;
        Dfs(vertexes_[neighbour], false);
        v.time_up = std::min(v.time_up, vertexes_[neighbour].time_up);

        if (!is_root && v.time_in <= vertexes_[neighbour].time_up) {
          articulation_points_.insert(v.index);
        }
      }
    }

    if (is_root && children > 1) {
      articulation_points_.insert(v.index);
    }
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  std::cin >> begin >> end;
  --begin;
  --end;
  g.edges_[begin].push_back(end);
  g.edges_[end].push_back(begin);

  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  for (int i = 0; i < n; ++i) {
    if (!g.GetVertexes()[i].visited) {
      g.Dfs(g.GetVertexes()[i], true);
    }
  }

  std::cout << g.GetArticulationPoints().size() << std::endl;

  for (auto x : g.GetArticulationPoints()) {
    std::cout << x + 1 << std::endl;
  }

  return 0;
}