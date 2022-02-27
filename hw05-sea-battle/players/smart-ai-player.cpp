#include "players/smart-ai-player.h"

std::pair<int, int> smart_ai_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  if (flag) {

    for (auto direction : field_t::DIRECTIONS) {
      int offset = 1;
      while (field_t::is_cell_valid(x + direction.first * offset, y + direction.second * offset)) {
        if (enemy_field[x + direction.first * offset][y + direction.second * offset] == field_t::EMPTY_CELL &&
            cells_next_to_ships.find({x + direction.first * offset, y + direction.second * offset}) ==
                cells_next_to_ships.end()) {

          return {x + direction.first * offset, y + direction.second * offset};
        } else if (enemy_field[x + direction.first * offset][y + direction.second * offset] != field_t::HIT_CELL) {

          break;
        }
        offset++;
      }
    }
    return {-1, -1};
  }

  for (int i = 0; i < field_t::FIELD_SIZE; i++) {
    for (int j = 0; j < field_t::FIELD_SIZE; j++) {
      if (enemy_field[i][j] == field_t::HIT_CELL) {
        for (auto direction : field_t::DIRECTIONS) {
          cells_next_to_ships.insert({i + direction.first, j + direction.second});
        }
      }
    }
  }
  while (enemy_field[x][y] != field_t::EMPTY_CELL || cells_next_to_ships.find({x, y}) != cells_next_to_ships.end()) {
    x++;
    if (x == field_t::FIELD_SIZE) {
      x = 0;
      y++;
    }
  }
  return {x, y};
}

void smart_ai_player_t::on_incorrect_move(int, int) {}
void smart_ai_player_t::on_duplicate_move(int, int) {}
void smart_ai_player_t::on_miss(int, int) {}
void smart_ai_player_t::on_hit(int, int) {
  flag = true;
}
void smart_ai_player_t::on_kill(int, int) {
  flag = false;
}
void smart_ai_player_t::on_win() {}
void smart_ai_player_t::on_lose() {}