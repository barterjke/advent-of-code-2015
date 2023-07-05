#include "header.hpp"

int part_1(const vector<string> &lines) {
  auto total = 0;
  for (auto &line : lines) {
    auto sizes = split(line, "x");
    assert(sizes.size() == 3);
    int l = stoi(sizes[0]), w = stoi(sizes[1]), h = stoi(sizes[2]);
    total +=
        2 * l * w + 2 * w * h + 2 * h * l + fmin(fmin(l * w, w * h), h * l);
  }
  return total;
}

int part_2(const vector<string> &lines) {
  auto total = 0;
  for (auto &line : lines) {
    auto sizes = split(line, "x");
    assert(sizes.size() == 3);
    int l = stoi(sizes[0]), w = stoi(sizes[1]), h = stoi(sizes[2]);
    total += fmin(fmin(l + w, w + h), h + l) * 2;
    total += l * w * h;
  }
  return total;
}

int main() {
  auto lines = read_file_by_lines("input/day2.txt");
  // cout << lines << std::endl;
  cout << "Part 1 answer " << part_1(lines) << "\n";
  cout << "Part 2 answer " << part_2(lines) << "\n";
  return 0;
}