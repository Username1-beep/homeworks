#include "field-checker.h"
#include <set>

std::set<int> get_row_as_set(const std::vector<std::vector<int>> &field, int x) {
  std::set<int> res;
  for (int i = 0; i < 9; ++i) {
    res.insert(field[x][i]);
  }
  return res;
}

std::set<int> get_col_as_set(const std::vector<std::vector<int>> &field, int y) {
  std::set<int> res;
  for (int i = 0; i < 9; ++i) {
    res.insert(field[i][y]);
  }
  return res;
}

std::set<int> get_sqr_as_set(const std::vector<std::vector<int>> &field, int sqr_x, int sqr_y) {
  std::set<int> res;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      res.insert(field[sqr_x + i][sqr_y + j]);
    }
  }
  return res;
}


bool check_field(const std::vector<std::vector<int>> &init_field, const std::vector<std::vector<int>> &solution) {
  // проверяем что заполненные клетки в init_field не изменены
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (solution[i][j] != init_field[i][j] && init_field[i][j] > 0) {
        return false;
      }
    }
  }

  std::set<int> correct_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // проверяем строчки и столбцы на правильность
  for (int i = 0; i < 9; ++i) {
    if (get_row_as_set(solution, i) != correct_values) {
      return false;
    }
    if (get_col_as_set(solution, i) != correct_values) {
      return false;
    }
  }
  // проверяем квадраты на правильность
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (get_sqr_as_set(solution, i * 3, j * 3) != correct_values) {
        return false;
      }
    }
  }
  return true; // в случае если все проверки пройдены
}
