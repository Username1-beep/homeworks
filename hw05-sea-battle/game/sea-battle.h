#pragma once

#include <memory>

#include "game/field.h"
#include "players/player-interface.h"

class sea_battle_t {
public:
  enum turn_t { FIRST_PLAYER = 0, SECOND_PLAYER = 1 };

  sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1, std::shared_ptr<player_interface_t> player2,
               field_t field2);

  ~sea_battle_t() = default;

  void play();

  static turn_t change_turn(turn_t current_turn);
  static std::string get_player_name(turn_t turn);

private:
  field_t delete_ships(field_t f);

  bool check_kill(field_t &f, int i, int j);

  bool check_win(field_t &f);

  field_t f1;
  field_t f2;

  std::shared_ptr<player_interface_t> my_player_ptr;
  std::shared_ptr<player_interface_t> enemy_player_ptr;

  field_t *my_field_ptr;
  field_t *enemy_field_ptr;
};
