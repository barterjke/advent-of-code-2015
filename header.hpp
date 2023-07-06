#include <sys/_types/_int8_t.h>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>


using std::cout, std::vector, std::string, std::endl, std::unordered_set;

vector<string> read_file_by_lines(const char *path) {
  std::fstream file(path);
  assert(file.is_open());
  string input;
  vector<string> result;
  while (std::getline(file, input)) {
    result.push_back(input);
  }
  return result;
}

vector<string> split(const string & s, const string & delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

template <typename T> std::ostream &operator<<(std::ostream &os, const vector<T> & v) {
  os << "v[";
  for (const auto &el : v) {
    os << el << (&el == &v.back() ? "]" : ", ");
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const vector<string> & v) {
  os << "v[";
  for (const auto &el : v) {
    os << std::quoted(el.substr(0, 50) + (el.size() > 50 ? ".." : ""))
       << (&el == &v.back() ? "]" : ", ");
  }
  return os;
}

template <typename K, typename V> std::ostream &operator<<(std::ostream &os, std::unordered_map<K, V> m) {
  os << "{";
  auto i = 0;
  for (auto &[k , v] : m) {
    os << k << ": " << v << (++i == m.size() ? "}" : ", ");
  }
  return os;
}

struct Vec2 {
  int x;
  int y;
  bool operator==(const Vec2 &rhs) const { return x == rhs.x && y == rhs.y; }
  struct HashFunction {
    size_t operator()(const Vec2 &point) const {
      return std::hash<int>()(point.x) + std::hash<int>()(point.y);
    }
  };
};

std::ostream &operator<<(std::ostream &os, Vec2 v) {
  return os << "Vec2(" << v.x << ", " << v.y << ")"; 
}