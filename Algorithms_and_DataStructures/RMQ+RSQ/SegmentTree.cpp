/*
 Если ты не можешь бросить старый зонтик, то как мы можем бросить тебя — старого друга? Ты ведь тоже часть нашей биографии.

Наконец-то к популярному среди старшего поколения явлению потянулась и перспективная молодежь. Крош изучает тренды Шар-Тока и пытается найти лучших кандидатов для совместного видео. Чтобы видео залетело в тренды, нашему другу нужно знать, сколько именно смешариков в конкретном творческом объединении имеет максимальное число подписчиков.

Если вы вдруг забыли, то напомним, что все выборы в Шарараме примечательны тем, что любой подотрезок ряда является творческим объединением.

 Формат ввода
В первой строке вводится одно натуральное число N ~--- количество смешариков в ряду.

Во второй строке вводятся N чисел ~--- количество подписчиков у смешарика.

В третьей строке вводится одно натуральное число K ~--- количество запросов Кроша.

В следующих K строках вводится по два числа ~--- номера левого и правого смешарика, границ творческого объединения (в 1-индексации).

Формат вывода
Для каждого запроса выведите в отдельной строке через пробел максимальное количество подписчиков у смешарика в указанном объединении и количество смешариков с числом подписчиков, равным максимальному.
 */

#include <iostream>
#include <vector>

class SegmentTree{
  public:
  int Parent(int index) const {
    return (index - 1) / 2;
  }
  int Left(int index) const {
    return 2 * index + 1;
  }
  int Right(int index) const {
    return 2 * index + 2;
  }
  SegmentTree(const std::vector<int> &initials_num){
    size_t size=1;
    while(size<initials_num.size()){
      size*=2;
    }
    segmentTree.resize(2*size-1);
     for (int i = 0; i < initials_num.size(); ++i) {
      segmentTree[i + size - 1] = std::pair(initials_num[i], 1);
    }
    for (int i = initials_num.size(); i < size; ++i) {
      segmentTree[i + size - 1] = std::pair(0, 0);
    }
    for (int i = size - 2; i >= 0; --i) {
      segmentTree[i].first = std::max(segmentTree[Left(i)].first, segmentTree[Right(i)].first);
      if (segmentTree[Left(i)].first == segmentTree[Right(i)].first) {
        segmentTree[i].second = segmentTree[Left(i)].second + segmentTree[Right(i)].second;
      } else {
        if (segmentTree[i].first == segmentTree[Left(i)].first) {
          segmentTree[i].second = segmentTree[Left(i)].second;
        } else {
          segmentTree[i].second = segmentTree[Right(i)].second;
        }
      }
    }
  }

std::pair<int, int> Query(int left, int right) const {
    left += segmentTree.size() / 2;
    right += segmentTree.size() / 2;
    int copy_left = left;
    int copy_right = right;
    int max = 0;
    int count = 0;
    while (left < right) {
      if (left == Right(Parent(left))) {
        max = std::max(max, segmentTree[left].first);
      }
      left = Parent(left + 1);
      if (right == Left(Parent(right))) {
        max = std::max(max, segmentTree[right].first);
      }
      right = Parent(right - 1);
    }
    if (left == right) {
      max = std::max(max, segmentTree[left].first);
    }
    left = copy_left;
    right = copy_right;
    while (left < right) {
      if (left == Right(Parent(left)) && max == segmentTree[left].first) {
        count += segmentTree[left].second;
      }
      left = Parent(left + 1);
      if (right == Left(Parent(right)) && max == segmentTree[right].first) {
        count += segmentTree[right].second;
      }
      right = Parent(right - 1);
    }
    if (left == right && max == segmentTree[left].first) {
      count += segmentTree[left].second;
    }
    std::pair<int, int> result(max, count);
    return result;
  }


 private:
 std::vector<std::pair<int,int>> segmentTree;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int size, q, left, right;
  int tmp;
  std::cin >> size;
  std::vector<int> initial_nums;
  initial_nums.resize(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> tmp;
    initial_nums[i] = tmp;
  }
  SegmentTree segment_tree(initial_nums);
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::cin >> left >> right;
    left--;
    right--;
    std::pair<int, int> pair = segment_tree.Query(left, right);
    std::cout << pair.first << " " << pair.second << "\n";
  }
  return 0;
}
