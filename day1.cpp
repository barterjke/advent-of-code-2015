#include "header.hpp"

int part_1(const vector<string> &lines) {
  int floor = 0;
  for (char c : lines[0]) {
    c == '(' ? floor++ : floor--;
  }
  return floor;
}

int part_2(const vector<string> &lines) {
  int floor = 0, index = 0;
  for (char c : lines[0]) {
    index++;
    c == '(' ? floor++ : floor--;
    if (floor == -1)
      return index;
  }
  return floor;
}

int main() {
  auto lines = read_file_by_lines("input/day1.txt");
  cout << "Part 1 answer " << part_1(lines) << "\n";
  cout << "Part 2 answer " << part_2(lines) << "\n";
  return 0;
}