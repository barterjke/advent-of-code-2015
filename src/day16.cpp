#include "header.hpp"

string without_last(const string &str) { return str.substr(0, str.size() - 1); }

int find_auntie(const vector<string> &aunties, const bool is_exact = true) {
    auto properties = read_file_by_lines("input/day_16_0.txt");
    std::unordered_map<string, int> right_auntie;
    for (auto &property : properties) {
        auto s            = split(property, " ");
        auto key          = without_last(s[0]);
        auto value        = stoi(s[1]);
        right_auntie[key] = value;
    }
    int count = 1;
    for (auto &auntie : aunties) {
        // Sue 436: cars: 9, trees: 0, goldfish: 0
        bool is_right = true;
        auto s        = split(auntie, " ");
        for (int i = 2; i < s.size(); i += 2) {
            auto key        = without_last(s[i]);
            auto value      = stoi(s[i + 1]);
            auto is_less    = key == "goldfish" || key == "pomeranians";
            auto is_greater = key == "cats" || key == "trees";
            auto cmp        = [&](auto x, auto y) {
                if (is_exact || (!is_less && !is_greater)) return x == y;
                if (is_less) return x < y;
                return x > y;
            };
            auto correct = right_auntie.contains(key) && cmp(value, right_auntie.at(key));
            if (!correct) {
                is_right = false;
                break;
            }
        }
        if (is_right) return count;
        count++;
    }
    unreachable;
}

int main() {
    auto lines = read_file_by_lines("input/day_16.txt");
    print("Part 1 answer is:", find_auntie(lines));
    print("Part 2 answer is:", find_auntie(lines, false));
    return 0;
}