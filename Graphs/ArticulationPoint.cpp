// Найдите точки сочленения в неориентированном графе.

// Формат ввода
// Первая строка входного файла содержит два натуральных числа n и m — количества вершин и рёбер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).
// Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).
// Формат вывода
// Первая строка выходного файла должна содержать одно натуральное число b — количество точек сочленения в заданном графе. На следующих b строках выведите b целых чисел — номера вершин, которые являются точками сочленения, в возрастающем порядке.

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

enum COLOURS { WHITE, GRAY, BLACK };


class Graph{
    private:
     std::vector<std::vector<size_t>> neighbors;
     std::vector<COLOURS> colors;
     std::vector<size_t> time_in;
     std::vector<size_t> time_up;
     std::set<size_t> articulationPoint;
    public:
     explicit Graph(size_t size): neighbors(size), colors(size, WHITE), time_in(size), time_up(size){

     }  
     void AddNewNoOrientEdge(size_t first, size_t second){
        neighbors[first].push_back(second);
        neighbors[second].push_back(first);
     } 

     void DFS(size_t ver, bool is_root, size_t time, size_t amountOfChildren){
        colors[ver] = GRAY;
        time_in[ver]= time_up[ver] = time++;
        for(size_t u: neighbors[ver]){
            if(colors[u] == GRAY){
                time_up[ver] = std::min(time_up[ver], time_in[u]);
            }
            if(colors[u] == WHITE){
                ++amountOfChildren;
                DFS(u, false, time, amountOfChildren);
                time_up[ver] = std::min(time_up[ver], time_up[u]);
                if(!is_root && time_in[ver]<=time_up[u]){
                    if(articulationPoint.find(ver) == articulationPoint.end()){
                        articulationPoint.emplace(ver);
                    }
                }
            }
        }

        if(is_root && amountOfChildren>1){
            if(articulationPoint.find(ver) == articulationPoint.end()){
                articulationPoint.emplace(ver);
            }
        }
        colors[ver] = BLACK;
     }

     void CountAllArticulationPoints() {
       for (size_t ver = 0; ver < neighbors.size(); ++ver) {
         if (colors[ver] == WHITE) {
          DFS(ver, true, 0, 0);
        }
    }
  }

  size_t GetAmountArticulationPoints() const {
    return neighbors.size();
  }

  void PrintAllArticulationPointsInSortedOrder() {
    for (size_t u : articulationPoint) {
      std::cout << u + 1 << "\n";
    }
  }

};


int main(){
size_t amount_of_vertexes, amount_of_edges;
  size_t ver_first, ver_second;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> ver_first >> ver_second;
    graph.AddNewNoOrientEdge(--ver_first, --ver_second);
  }
  graph.CountAllArticulationPoints();
  std::cout << graph.GetAmountArticulationPoints() << "\n";
  graph.PrintAllArticulationPointsInSortedOrder();
  return 0;
}