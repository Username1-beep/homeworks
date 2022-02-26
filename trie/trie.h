#pragma once

#include <string>
#include <vector>

#include <map>

class trie_t {
public:
  trie_t();
  ~trie_t();

  trie_t(const trie_t &other);
  trie_t &operator=(const trie_t &other);

  void insert(const std::string &str);

  bool erase(const std::string &str);

  void clear();

  bool find(const std::string &str) const;

  size_t count_with_prefix(const std::string &prefix) const;

  std::string operator[](size_t index) const;

  std::vector<std::string> to_vector() const;

  size_t size() const;

  bool empty() const;

  void swap(trie_t &other);

private:
  std::map<char, trie_t> next_layer{}; // следующий слой дерева
  int64_t cell_count{0};    // количество строк кончающихся в данной ячейке
  int64_t subtree_count{0}; // в данной и всех следующих
};
