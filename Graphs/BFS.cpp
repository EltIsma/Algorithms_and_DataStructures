// Вам дан неориентированный граф. Найдите кратчайший путь от вершины a до вершины b.

// Формат ввода
// В первой строке входного файла идут целые числа n и m (1 ≤ n ≤ 50 000, 1 ≤ m ≤ 100 000) — количества вершин и рёбер соответственно. Во второй строке идут целые числа a и b — стартовая и конечная вершины соответственно. Далее идут m строк, описывающих рёбра.
// Формат вывода
// Если пути между a и b нет, выведите единственное число -1. Иначе выведите в первой строке число l — длину кратчайшего пути между этими двумя вершинами в рёбрах, а во второй строке выведите l + 1 число — вершины этого пути.


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>


class Graph{
   public:
    explicit Graph(size_t size){
        neighbors.resize(size);
        parent.resize(size);
        distance.resize(size, max_dist);
    }
    void BFS(int ver){
        std::queue<int> queue;
        int parent_;
        queue.push(ver);
        distance[ver] = 0;
        parent[ver] = -1;

        while(!queue.empty()){
            parent_ = queue.front();
            queue.pop();
            for(size_t i =0; i< neighbors[parent_].size();i++){
                if (distance[neighbors[parent_][i]] == max_dist){
                    distance[neighbors[parent_][i]] = distance[parent_]+1;
                    parent[neighbors[parent_][i]] = parent_;
                    queue.push(neighbors[parent_][i]);
                }
            }

        }
    }

    void AddUndirectedEdge(size_t first, size_t second){
        if(std::find(neighbors[first].begin(), neighbors[second].end(), second) == neighbors[first].end()){
               neighbors[first].push_back(second);
               neighbors[second].push_back(first);
        }
    }

    int GetTheSmallestDistance(int ver){
        if (distance[ver] == max_dist){
            return -1;
        }
        return distance[ver];
    }

    void PrintWay(int ver) {
        if(parent[ver]==-1){
            std::cout<<ver+1<<" ";
            return;
        }
        PrintWay(parent[ver]);
        std::cout<< ver+1<<" ";
    }
    private:
      std::vector<std::vector<size_t>> neighbors;
      std::vector<int> parent;
      std::vector<int> distance;
      const int max_dist = 500000;
};

int main(){
      size_t n, m;
  int a, b;
  size_t first, second;
  std::cin >> n >> m;
  std::cin >> a >> b;
  --a;
  --b;
  Graph graph(n);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> first >> second;
    --first;
    --second;
    graph.AddUndirectedEdge(first, second);
  }
  graph.BFS(a);
  int dist = graph.GetTheSmallestDistance(b);
  std::cout << dist << "\n";
  if (dist != -1) {
    graph.PrintWay(b);
  }
}