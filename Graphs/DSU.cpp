// Одно разбросанное на островах Океании государство решило создать сеть автомобильных дорог (вернее, мостов). По каждому мосту можно перемещаться в обе стороны. Был разработан план очередности строительства мостов и известно, что после постройки всех мостов можно будет проехать по ним с каждого острова на каждый (возможно, через некоторые промежуточные острова).
// Однако, этот момент может наступить до того, как будут построены все мосты. Ваша задача состоит в определении такого минимального количества мостов, после постройки которого (в порядке строительства по плану) можно будет попасть с любого острова на любой другой.

// Формат ввода
// Первая строка содержит два числа: N — число островов (1 ≤ N ≤ 100000) и M — количество мостов в плане (1 ≤ M ≤ 200000). В каждой следующей строке содержится описание моста — два числа x и y (0 ≤ x, y < N) — номера соединяемых островов.
// Формат вывода
// Выведите в выходной файл одно число — минимальное количество построенных мостов, по которым можно попасть с любого острова на любой.

#include <iostream>
#include <vector>
class DSU{
    private:
    std::vector<size_t> parents;
    std::vector<size_t> rank;
    size_t minAmountOfBridges;
    size_t amountOfUnits;


    public:
    explicit DSU(size_t size){
        parents.resize(size);
        for(size_t i =0; i<size; i++){
            parents[i] = i;
        }

        rank.resize(size, 0);
        minAmountOfBridges =0;
        amountOfUnits = 0;
    }

    size_t FindSet(size_t x){
        if(x == parents[x]){
            return x;
        }

        parents[x] = FindSet(parents[x]);
    }
    void Union(size_t x, size_t y) {
     x = FindSet(x);
     y = FindSet(y);
    if (rank[x] < rank[y]) {
      parents[x] = y;
    } else if (rank[x] > rank[y]) {
      parents[y] = x;
    } else {
      parents[x] = y;
      rank[y]++;
    }
    amountOfUnits++;
  }

  void IncreaseCounter() {
    if (amountOfUnits != parents.size() - 1) {
      minAmountOfBridges++;
    }
  }

  size_t GetMinAmountOfBridge() const {
    return minAmountOfBridges;
  }


};

int main() {
  size_t amount_of_islands, amount_of_bridges;
  size_t first_island, second_island;
  std::cin >> amount_of_islands >> amount_of_bridges;
  DSU dsu(amount_of_islands);
  for (size_t i = 0; i < amount_of_bridges; ++i) {
    std::cin >> first_island >> second_island;
    dsu.IncreaseCounter();
    if (dsu.FindSet(first_island) != dsu.FindSet(second_island)) {
      dsu.Union(first_island, second_island);
    }
  }
  std::cout << dsu.GetMinAmountOfBridge();
  return 0;
}

