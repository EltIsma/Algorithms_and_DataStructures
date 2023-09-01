// Дан ориентированный невзвешенный граф. Необходимо определить есть ли в нём циклы, и если есть, то вывести любой из них.

// Формат ввода
// В первой строке входного файла находятся два натуральных числа N и M (1 ≤ N ≤ 100000, M ≤ 100000) — количество вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел — номерами начальной и конечной вершин соответственно.
// Формат вывода
// Если в графе нет цикла, то вывести NO, иначе — YES и затем перечислить все вершины в порядке обхода цикла.


#include <iostream>
#include <vector>

enum COLOR {
    WHITE,
    GREY,
    BLACK,
};

class Graph{
    public:
      explicit Graph(size_t size){
        neighbors.resize(size);
        colors.resize(size, WHITE);
      }

      void DFS(size_t ver){
        if(has_cycle){
            return;
        }
        colors[ver] = GREY;
        cycle.push_back(ver);

        for(auto u: neighbors[ver]){
            if(colors[u] == WHITE){
                DFS(u);
            } else if(colors[u] == GREY){
                has_cycle = true;
                cycle.push_back(u);
                return;
            }
        }

        colors[ver] = BLACK;
        cycle.pop_back();
      }

      bool HasCycle(){
        for(size_t v=0; v<colors.size(); v++){
            if(colors[v] == WHITE){
                DFS(v);
                if(has_cycle){
                    break;
                }
            }
        }
        return has_cycle;
      }

      void InsertEdgeOriented(size_t first, size_t second){
        neighbors[first].push_back(second);
      }

      void PrintCycle() const {
       size_t end = cycle.back();
       size_t index = cycle.size() - 2;
       while (cycle[index] != end) {
         --index;
        }
       for (; index < cycle.size() - 1; index++) {
         std::cout << cycle[index] + 1 << " ";
        }
  }

    private:

    bool has_cycle = false;
    std::vector<COLOR> colors;
    std::vector<std::vector<size_t>> neighbors;
    std::vector<size_t> cycle;
};


int main() {
  size_t amount_of_vertexes, amount_of_edges;
  size_t ver_first, ver_second;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> ver_first >> ver_second;
    ver_first--;
    ver_second--;
    graph.InsertEdgeOriented(ver_first, ver_second);
  }
  if (graph.HasCycle()) {
    std::cout << "YES\n";
    graph.PrintCycle();
  } else {
    std::cout << "NO";
  }
  return 0;
}