#include "header.hpp"

int part_1(const vector<string> &lines) {
    Vec2 position = {0, 0};
    assert(lines.size() == 1);
    std::unordered_set<Vec2, Vec2::HashFunction> visited = {position};
    for (char c : lines[0]) {
        switch (c) {
        case '<':
            position.x--;
            break;
        case '^':
            position.y--;
            break;
        case 'v':
            position.y++;
            break;
        case '>':
            position.x++;
            break;
        }
        visited.insert(position);
    }
    return visited.size();
}

int part_2(const vector<string> &lines) {
    Vec2 position_1 = {0, 0}, position_2 = {0, 0};
    assert(lines.size() == 1);
    std::unordered_set<Vec2, Vec2::HashFunction> visited = {position_1};
    bool turn                                       = true;
    for (char c : lines[0]) {
        turn           = !turn;
        auto &position = turn ? position_1 : position_2;
        switch (c) {
        case '<':
            position.x--;
            break;
        case '^':
            position.y--;
            break;
        case 'v':
            position.y++;
            break;
        case '>':
            position.x++;
            break;
        }
        visited.insert(position);
    }
    return visited.size();
}

int main() {
    auto lines = read_file_by_lines("input/day_3.txt");
    // cout << lines << std::endl;
    cout << "Part 1 answer: " << part_1(lines) << "\n";
    cout << "Part 2 answer: " << part_2(lines) << "\n";
    return 0;
}