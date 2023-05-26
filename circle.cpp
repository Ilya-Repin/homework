#include <iostream>
#include <vector>
#include <unordered_set>

enum Color { WHITE, GREY, BLACK };

class Graph {
 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> circle_;

  bool DFSVisit(size_t vertex, std::vector<Color> &visited) {
    visited[vertex] = GREY;

    for (auto neighbour : vertexes_[vertex]) {
      if (visited[neighbour] == WHITE) {
        circle_.push_back(neighbour);

        if (DFSVisit(neighbour, visited)) {
          return true;
        }

        circle_.pop_back();
      } else if (visited[neighbour] == GREY) {
        size_t neighbour_ind = 0;

        for (size_t i = 0; i < circle_.size(); ++i) {
          if (neighbour == circle_[i]) {
            neighbour_ind = i;
            break;
          }
        }

        circle_ = std::vector(circle_.begin() + neighbour_ind, circle_.end());

        return true;
      }
    }

    visited[vertex] = BLACK;

    return false;
  }

 public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
    circle_ = std::vector<int>();
  }

  void FindCircle() {
    std::vector<Color> visited(vertexes_.size(), WHITE);

    for (size_t i = 0; i < vertexes_.size(); ++i) {
      if (visited[i] == WHITE) {
        circle_.push_back(i);

        if (DFSVisit(i, visited)) {
          std::cout << "YES"
                    << "\n";

          for (size_t x = 0; x < circle_.size(); ++x) {
            std::cout << circle_[x] + 1 << " ";
          }

          return;
        }
      }
    }

    std::cout << "NO";
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].insert(end);

  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.FindCircle();

  return 0;
}