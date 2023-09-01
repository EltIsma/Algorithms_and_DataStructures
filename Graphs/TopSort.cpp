#include <iostream>
#include <vector>

enum COLOR {
    WHITE,
    GREY,
    BLACK,
};

class Graph{
    public:

      explicit Graph(size_t size) : colors(size, WHITE), neighbors(size), sorted_array(size), count(size - 1) {
      }
    

      void TopSort(){
        for(size_t v=0; v<colors.size(); v++){
            if(colors[v] == WHITE){
                DFS(v);
            }
        }
      }

      void InsertEdgeOriented(size_t first, size_t second){
        neighbors[first].push_back(second);
      }

      void PrintSortedGraph() {
        if (is_able_to_sort) {
        for (size_t i = 0; i < sorted_array.size(); i++) {
          std::cout << sorted_array[i] + 1 << " ";
        }
        } else {
           std::cout << -1;
        }
  }

    private:
    void DFS(size_t ver){
        colors[ver] = GREY;
        for(auto u: neighbors[ver]){
            if(colors[u] == WHITE){
                DFS(u);
            } else if(colors[u] == GREY){
                is_able_to_sort = false;
            }
        }

        colors[ver] = BLACK;
        sorted_array[count] = ver;
        count--;
        
      }
    bool is_able_to_sort = false;
    std::vector<COLOR> colors;
    std::vector<std::vector<size_t>> neighbors;
    std::vector<size_t> sorted_array;
    size_t count;
};


int main() {
  size_t amount_of_pekuses, amount_of_pairs;
  size_t first_pekus, second_pekus;
  std::cin >> amount_of_pekuses >> amount_of_pairs;
  Graph graph(amount_of_pekuses);
  for (size_t i = 0; i < amount_of_pairs; ++i) {
    std::cin >> first_pekus >> second_pekus;
    graph.InsertEdgeOriented(--first_pekus, --second_pekus);
  }
  graph.TopSort();
  graph.PrintSortedGraph();
  return 0;
}