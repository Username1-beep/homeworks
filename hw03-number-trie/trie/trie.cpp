#include "trie.h"

trie_t::trie_t() = default;
trie_t::~trie_t() = default;
trie_t::trie_t(const trie_t &other) = default;
trie_t &trie_t::operator=(const trie_t &other) = default;

void trie_t::insert(const std::string &str) {
  ++subtree_count;
  if (str.length() == 0) {
    ++cell_count;
    return;
  }
  next_layer[str[0]].insert(str.substr(1));
}

bool trie_t::erase(const std::string &str) {
  if (str.length() == 0) {
    if (cell_count > 0) {
      --subtree_count;
      --cell_count;
      return true;
    } else {
      return false;
    }
  }
  if (next_layer.find(str[0]) == next_layer.end()) {
    return false;
  }
  if (next_layer[str[0]].erase(str.substr(1))) {
    --subtree_count;
    return true;
  }
  return false;
}

void trie_t::clear() {
  next_layer.clear();
  cell_count = 0;
  subtree_count = 0;
}

bool trie_t::find(const std::string &str) const {
  if (str.length() == 0) {
    return true;
  }
  if (next_layer.find(str[0]) == next_layer.end()) {
    return false;
  }
  return next_layer.at(str[0]).find(str.substr(1));
}

size_t trie_t::count_with_prefix(const std::string &prefix) const {
  if (prefix.length() == 0) {
    return subtree_count;
  }
  if (next_layer.find(prefix[0]) == next_layer.end()) {
    return 0;
  }
  return next_layer.at(prefix[0]).count_with_prefix(prefix.substr(1));
}

std::string trie_t::operator[](size_t index) const {
  if (index < cell_count) {
    return "";
  }
  index -= cell_count;
  for (const auto &cell : next_layer) {
    if (index < cell.second.subtree_count) {
      // если мы остановились в нужной ветке
      return cell.first + cell.second[index];
    } else {
      index -= cell.second.subtree_count;
    }
  }
}

std::vector<std::string> trie_t::to_vector() const {
  std::vector<std::string> string_vector{};
  for (int i = 0; i < cell_count; ++i) {
    string_vector.push_back("");
  }
  for (const auto &cell : next_layer) {
    std::vector<std::string> subtree_vector = cell.second.to_vector();
    for (std::string &str : subtree_vector) {
      str = cell.first + str;
    }
    string_vector.insert(string_vector.end(), subtree_vector.begin(), subtree_vector.end());
  }
  return string_vector;
}

size_t trie_t::size() const {
  return subtree_count;
}

bool trie_t::empty() const {
  return subtree_count == 0;
}

void trie_t::swap(trie_t &other) {
  std::swap(*this, other);
}
