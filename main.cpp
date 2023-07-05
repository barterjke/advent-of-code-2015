#include "header.hpp"
#include <unordered_map>
#include <unordered_set>

const unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
const unordered_set<string> bad_pairs = {"ab", "cd", "pq", "xy"};

bool is_nice(const string &input) {
  int vowels_counter = vowels.find(input[0]) != vowels.end();
  bool contains_tweens = false;
  for (auto i = 1; i < input.size(); i++) {
    char prev = input[i - 1], c = input[i];
    if (vowels.find(c) != vowels.end()) {
      vowels_counter++;
    }
    if (!contains_tweens && prev == c) {
      contains_tweens = true;
    }
    if (bad_pairs.find(string() + prev + c) != bad_pairs.end()) {
      return false;
    }
  }
  return contains_tweens && vowels_counter >= 3;
}

int part_1(const vector<string> &lines) {
  auto nice_counter = 0;
  for (auto &line : lines) {
    nice_counter += is_nice(line);
  }
  return nice_counter;
}

int part_2(const vector<string> &lines) { return 0; }

int main() {
  assert(is_nice("ugknbfddgicrmopn"));
  assert(is_nice("aaa"));
  assert(!is_nice("jchzalrnumimnmhp"));
  assert(!is_nice("haegwjzuvuyypxyu"));
  assert(!is_nice("dvszwmarrgswjxmb"));
  auto lines = read_file_by_lines("input/day5.txt");
  cout << "Part 1 answer: " << part_1(lines) << "\n";
  cout << "Part 2 answer: " << part_2(lines) << "\n";
  return 0;
}