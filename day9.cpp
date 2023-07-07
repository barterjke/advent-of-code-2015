#include "header.hpp"
#include <_types/_uint32_t.h>
#include <cassert>
#include <limits>
#include <unordered_set>
#include <vector>

unordered_set<string> distinct_locations;

int get_index(const string &s) {
    return std::distance(distinct_locations.begin(), distinct_locations.find(s));
}

void combinations(int length, vector<int> &pos, vector<vector<int>> &result, int n) {
    if (n == length) {
        result.push_back(pos);
        return;
    }
    for (int i = 0; i < length; i++) {
        bool skip = false;
        for (int j = 0; j < n; j++) {
            if (pos[j] == i) {
                skip = true;
                break;
            }
        }
        if (!skip) {
            pos[n] = i;
            combinations(length, pos, result, n + 1);
        }
    }
}

Vec2 part_1(const vector<string> &lines) {
    vector<std::tuple<string, string, int>> from_to_distance;
    std::unordered_map<Vec2, int, Vec2::HashFunction> weights;
    for (auto &line : lines) {
        auto s        = split(line, " ");
        auto from     = s[0];
        auto to       = s[2];
        auto distance = stoi(s[4]);
        distinct_locations.insert(from);
        distinct_locations.insert(to);
        from_to_distance.push_back({from, to, distance});
    }
    for (auto &[from, to, distance] : from_to_distance) {
        weights[{get_index(from), get_index(to)}] = distance;
        weights[{get_index(to), get_index(from)}] = distance;
    }
    vector<int> pos(distinct_locations.size(), 0);
    vector<vector<int>> result;
    combinations(pos.size(), pos, result, 0);
    auto min_distance = std::numeric_limits<int>::max();
    auto max_distance = 0;
    for (auto pos : result) {
        auto sum = 0;
        for (auto i = 0; i < pos.size() - 1; i++) {
            sum += weights.at({pos[i], pos[i + 1]});
        }
        min_distance = fmin(sum, min_distance);
        max_distance = fmax(sum, max_distance);
    }
    return Vec2{min_distance, max_distance};
}

int part_2(const vector<string> &lines) {
    auto result = 0;
    return result;
}

int main() {
    auto test_answer = part_1(read_file_by_lines("input/day9.0.txt"));
    assert(test_answer.x == 605 && test_answer.y == 982);
    distinct_locations.clear();
    auto lines        = read_file_by_lines("input/day9.txt");
    auto part1_answer = part_1(lines);
    cout << "Part 1 answer " << part1_answer.x << "\n";
    cout << "Part 2 answer " << part1_answer.y << "\n";
    return 0;
}