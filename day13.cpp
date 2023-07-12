#include "header.hpp"

void get_combinations_recursive(int length, vector<int> &pos, vector<vector<int>> &result, int n) {
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
            get_combinations_recursive(length, pos, result, n + 1);
        }
    }
}

vector<vector<int>> get_combinations(size_t size) {
    vector<int> pos(size, 0);
    vector<vector<int>> result;
    get_combinations_recursive(pos.size(), pos, result, 0);
}

int calculate_optimal_seating(const vector<string> &lines, bool include_self = false) {
    std::unordered_map<std::tuple<string, string>, int, HashFunction> map;
    std::unordered_set<string> names;
    if (include_self) names.insert("me");
    for (auto &line : lines) {
        // ex: "Eric would lose 47 happiness units by sitting next to David."
        auto s             = split(line, " ");
        string person      = s[0];
        int happiness      = stoi(s[3]);
        bool gain          = s[2] == "gain";
        string next_person = s[10].substr(0, s[10].size() - 1);
        // print(person, next_person, happiness, gain);
        // print(line, "\n");
        map[{person, next_person}] = (gain ? +1 : -1) * happiness;
        names.insert(person);
    }
    auto max_happines = 0;
    for (vector<int> comb : get_combinations(names.size())) {
        auto total = 0;
        for (int i = 0; i < comb.size(); i++) {
            auto it1 = names.begin();
            auto it2 = names.begin();
            std::advance(it1, comb[i]);
            if (i != comb.size() - 1)
                std::advance(it2, comb[i + 1]);
            else {
                std::advance(it2, comb[0]);
            }
            total += map[{*it1, *it2}];
            total += map[{*it2, *it1}];
        }
        max_happines = fmax(max_happines, total);
    }
    return max_happines;
}

int main() {
    assert(calculate_optimal_seating(read_file_by_lines("input/day_13_0.txt")) == 330);
    auto lines        = read_file_by_lines("input/day_13.txt");
    auto part1_answer = calculate_optimal_seating(lines);
    cout << "Part 1 answer " << part1_answer << "\n";
    auto part2_answer = calculate_optimal_seating(lines, true);
    cout << "Part 2 answer " << part2_answer << "\n";
}