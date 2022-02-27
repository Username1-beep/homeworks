#include "sudoku-solver.h"
#include <set>

std::set<int> possible_values(const std::vector<std::vector<int>> &field, int x, int y) {
  std::set<int> res = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // все возможные числа
  // исключаем числа которые есть в строчке и столбике
  for (int i = 0; i < 9; ++i) {
    if (field[x][i] > 0 && res.find(field[x][i]) != res.end()) {
      res.erase(res.find(field[x][i])); // удаляем число из возможных
    }
    if (field[i][y] > 0 && res.find(field[i][y]) != res.end()) {
      res.erase(res.find(field[i][y])); // удаляем число из возможных
    }
  }
  // находим индексы угла текущего квадрата
  int sqr_x = (x / 3) * 3;
  int sqr_y = (y / 3) * 3;
  // исключаем числа которые есть в квадрате
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (field[sqr_x + i][sqr_y + j] > 0 && res.find(field[sqr_x + i][sqr_y + j]) != res.end()) {
        res.erase(res.find(field[sqr_x + i][sqr_y + j])); // удаляем число из возможных
      }
    }
  }
  return res;
}

void rec(const std::vector<std::vector<int>> &field, std::vector<std::vector<std::vector<int>>> &all_solutions) {
  // находим индекс нуля
  int x;
  int y;
  bool zero_exists = false; // есть ли на поле ноль
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (field[i][j] == 0) {
        zero_exists = true;
        x = i;
        y = j;
      }
    }
  }

  if (zero_exists) {
    // поочередно подставляем каждое возможное число
    std::set<int> values = possible_values(field, x, y);
    for (auto iter = values.begin(); iter != values.end(); ++iter) {
      std::vector<std::vector<int>> next_field = field;
      next_field[x][y] = *iter; // подставляем число в новый массив
      rec(next_field, all_solutions); // вызываем рекурсию для нового поля
    }
  } else {
    all_solutions.push_back(field); // если поле заполнено, добавляем его в решения
  }
}

std::pair<size_t, std::vector<std::vector<int>>> sudoku_solve(const std::vector<std::vector<int>> &field) {
  std::vector<std::vector<std::vector<int>>> all_solutions; // сюда записываем все решения
  rec(field, all_solutions); // находим решения рекурсией
  return std::make_pair(all_solutions.size(), all_solutions[0]);
}
