#include "phone-book.h"

bool phone_book_t::create_user(const std::string &number, const std::string &name) {

  if (!(user_by_number(number) == INVALID_USER)) {
    return false;
  }

  user_info_t user{{number, name}, 0};

  name_users.insert(user);

  for (int i = 0; i <= number.length(); i++) {
    number_users[number.substr(0, i)].insert(user);
  }
  return true;
}

bool phone_book_t::add_call(const call_t &call) {

  user_info_t user = user_by_number(call.number);
  if (user == INVALID_USER) {
    return false;
  }

  calls.push_back(call);

  name_users.erase(user);
  for (int i = 0; i <= call.number.length(); i++) {
    number_users[call.number.substr(0, i)].erase(user);
  }
  user.total_call_duration_s += call.duration_s;
  name_users.insert(user);
  for (int i = 0; i <= call.number.length(); i++) {
    number_users[call.number.substr(0, i)].insert(user);
  }
  return true;
}

std::vector<call_t> phone_book_t::get_calls(size_t start_pos, size_t count) const {
  int pos1 = std::min(start_pos, calls.size());
  int pos2 = std::min(start_pos + count, calls.size());
  return std::vector<call_t>(calls.begin() + pos1, calls.begin() + pos2);
}

std::vector<user_info_t> phone_book_t::search_users_by_number(const std::string &number_prefix, size_t count) const {
  std::vector<user_info_t> v;
  if (number_users.find(number_prefix) != number_users.end()) {
    user_info_t user{{number_prefix, ""}, std::numeric_limits<double>::max()};
    for (auto i = number_users.at(number_prefix).lower_bound(user); i != number_users.at(number_prefix).end(); i++) {
      if (v.size() == count) {
        break;
      }
      if (i->user.number.length() < number_prefix.length() ||
          i->user.number.substr(0, number_prefix.length()) != number_prefix) {
        break;
      }
      v.push_back(*i);
    }
  }
  return v;
}

std::vector<user_info_t> phone_book_t::search_users_by_name(const std::string &name_prefix, size_t count) const {
  std::vector<user_info_t> v;
  user_info_t user{{"", name_prefix}, std::numeric_limits<double>::max()};
  for (auto i = name_users.lower_bound(user); i != name_users.end(); i++) {
    if (v.size() == count) {
      break;
    }
    if (i->user.name.length() < name_prefix.length() || i->user.name.substr(0, name_prefix.length()) != name_prefix) {
      break;
    }
    v.push_back(*i);
  }
  return v;
}

void phone_book_t::clear() {
  *this = phone_book_t();
}

size_t phone_book_t::size() const {
  return name_users.size();
}

bool phone_book_t::empty() const {
  return name_users.empty();
}

user_info_t phone_book_t::user_by_number(const std::string &number) {
  if (number_users.find(number) != number_users.end()) {
    for (const user_info_t &user : number_users[number]) {
      if (user.user.number == number) {
        return user;
      }
    }
  }
  return INVALID_USER;
}
