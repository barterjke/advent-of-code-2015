#include "header.hpp"

int part_1(const vector<string> &lines) {
    auto result = 0;
    for (auto &line : lines) {
        auto char_in_memory    = -2;
        bool prev_is_escape_ch = false;
        for (char c : line) {
            if (prev_is_escape_ch) {
                prev_is_escape_ch = false;
                char_in_memory++;
                if (c == 'x') {
                    char_in_memory -= 2;
                }
            } else if (c == '\\') {
                prev_is_escape_ch = true;
            } else {
                char_in_memory++;
            }
        }
        result += line.size() - char_in_memory;
    }
    return result;
}

int part_2(const vector<string> &lines) {
    auto result = 0;
    for (auto &line : lines) {
        for (char c : line) {
            if (c == '\\' || c == '"') result++;
        }
        result += 2;
    }
    return result;
}

int main() {
    auto lines = read_file_by_lines("input/day8.txt");
    assert(part_1(read_file_by_lines("input/day8.0.txt")) == 12);
    assert(part_2(read_file_by_lines("input/day8.0.txt")) == 19);
    auto part1_answer = part_1(lines);
    cout << "Part 1 answer " << part1_answer << "\n";
    auto part2_answer = part_2(lines);
    cout << "Part 2 answer " << part2_answer << "\n";
    return 0;
}