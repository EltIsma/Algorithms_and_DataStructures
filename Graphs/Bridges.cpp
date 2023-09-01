// Дан неориентированный граф. Требуется найти все мосты в нем.

// Формат ввода
// В первой строке входного файла два натуральных числа n и m (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000) –количество вершин и рёбер в графе соответственно. Далее в m строках перечислены рёбра графа. Каждое ребро задается парой чисел – номерами начальной и конечной вершин соответственно.
// Формат вывода
// Первая строка выходного файла должна содержать одно натуральное число b – количество мостов в заданном графе. На следующей строке выведите b чисел – номера ребер, которые являются мостами, в возрастающем порядке. Ребра нумеруются с единицы в том порядке, в котором они заданы во входном файле.

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

enum COLOURS { WHITE, GRAY, BLACK };

class Graph {
 private:
  std::vector<std::vector<std::pair<size_t, size_t>>> neighbors
  ;
  std::vector<std::vector<size_t>> vertexes_without_index_;
  std::vector<COLOURS> colors;
  std::vector<size_t> time_in;
  std::vector<size_t> time_up;
  std::set<size_t> bridges;

 public:
  explicit Graph(size_t size)
      : neighbors(size), vertexes_without_index_(size), colors(size, WHITE), time_in(size), time_up(size) {
  }

  void AddNewNoOrientEdge(size_t ver_first, size_t ver_second, size_t index) {
    neighbors
    [ver_second].emplace_back(index, ver_first);
    neighbors
    [ver_first].emplace_back(index, ver_second);
    vertexes_without_index_[ver_second].push_back(ver_first);
    vertexes_without_index_[ver_first].push_back(ver_second);
  }

  void DFS(size_t ver, size_t time, int parent) {
    colors[ver] = GRAY;
    time_in[ver] = time_up[ver] = time++;
    size_t u_ver, u_index_of_edge;
    for (std::pair<size_t, size_t> u : neighbors
    [ver]) {
      u_ver = u.second;
      u_index_of_edge = u.first;
      if (u_ver != static_cast<size_t>(parent) && colors[u_ver] == GRAY) {
        time_up[ver] = std::min(time_up[ver], time_in[u_ver]);
      }
      if (colors[u_ver] == WHITE) {
        DFS(u_ver, time, static_cast<int>(ver));
        time_up[ver] = std::min(time_up[ver], time_up[u_ver]);
        if (time_in[ver] < time_up[u_ver]) {
          if (bridges.find(u_index_of_edge) == bridges.end()) {
            if (std::count(vertexes_without_index_[ver].begin(), vertexes_without_index_[ver].end(), u_ver) == 1) {
              bridges.emplace(u_index_of_edge);
            }
          }
        }
      }
    }
    colors[ver] = BLACK;
  }

  void CountAllBridges() {
    for (size_t ver = 0; ver < neighbors
    .size(); ++ver) {
      if (colors[ver] == WHITE) {
        DFS(ver, 0, -1);
      }
    }
  }

  size_t GetAmountBridges() const {
    return bridges.size();
  }

  void PrintAllBridgesInSortedOrder() {
    for (size_t u : bridges) {
      std::cout << u << "\n";
    }
  }
};

int main() {
  size_t amount_of_vertexes, amount_of_edges;
  size_t ver_first, ver_second;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> ver_first >> ver_second;
    graph.AddNewNoOrientEdge(--ver_first, --ver_second, i + 1);
  }
  graph.CountAllBridges();
  std::cout << graph.GetAmountBridges() << "\n";
  graph.PrintAllBridgesInSortedOrder();
  return 0;
}