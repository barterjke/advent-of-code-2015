#include "header.hpp"

int part_1(const vector<string> &lines, bool is_part_2 = false) {
    enum cmd { toggle, on, off };
    int8_t grid[1000][1000] = {0};
    for (auto &line : lines) {
        auto s       = split(line, " ");
        auto command = s[0] == "toggle" ? toggle : (s[1] == "on" ? on : off);
        auto pos1    = split(s[2 - (command == toggle)], ",");
        auto pos2    = split(s[4 - (command == toggle)], ",");
        auto x1      = stoi(pos1[0]);
        auto y1      = stoi(pos1[1]);
        auto x2      = stoi(pos2[0]);
        auto y2      = stoi(pos2[1]);
        assert(x1 <= x2 && y1 <= y2);
        for (; x1 <= x2; x1++) {
            for (auto y1 = stoi(pos1[1]); y1 <= y2; y1++) {
                if (command == toggle) grid[x1][y1] = is_part_2 ? grid[x1][y1] + 2 : !grid[x1][y1];
                if (command == on) grid[x1][y1] = is_part_2 ? grid[x1][y1] + 1 : 1;
                if (command == off) grid[x1][y1] = is_part_2 ? fmax(grid[x1][y1] - 1, 0) : 0;
            }
        }
    }
    size_t counter = 0;
    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            counter += grid[i][j];
        }
    }
    return counter;
}

int main() {
    auto lines = read_file_by_lines("input/day_6.txt");
    cout << "Part 1 answer " << part_1(lines) << "\n";
    cout << "Part 2 answer " << part_1(lines, true) << "\n";
    return 0;
}