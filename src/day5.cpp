#include "header.hpp"

const std::unordered_set<char> vowels      = {'a', 'e', 'i', 'o', 'u'};
const std::unordered_set<string> bad_pairs = {"ab", "cd", "pq", "xy"};

bool is_nice_1(const string &input) {
    int vowels_counter   = vowels.find(input[0]) != vowels.end();
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

bool is_nice_2(const string &input) {
    // 1. It contains a pair of any two letters that appears at least twice in the string without
    // overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps). It
    // 2. contains at least one letter which repeats with exactly one letter between them, like xyx,
    // abcdefeghi (efe), or even aaa.
    std::map<string, int> pairs;
    bool one_letter_between    = false;
    bool contains_non_adj_pair = false;
    for (auto i = 0; i < input.size() - 1; i++) {
        one_letter_between =
            one_letter_between || (i + 2 < input.size() && input[i] == input[i + 2]);
        auto s = string() + input[i] + input[i + 1];
        if (contains_non_adj_pair) continue;
        contains_non_adj_pair =
            contains_non_adj_pair || (pairs.contains(s) && pairs.at(s) != i - 1);
        if (!pairs.contains(s)) {
            pairs[s] = i;
        }
    }
    return contains_non_adj_pair && one_letter_between;
}

int part_1(const vector<string> &lines, auto is_nice) {
    auto nice_counter = 0;
    for (auto &line : lines) {
        nice_counter += is_nice(line);
    }
    return nice_counter;
}

int main() {
    assert(is_nice_1("ugknbfddgicrmopn"));
    assert(is_nice_1("aaa"));
    assert(!is_nice_1("jchzalrnumimnmhp"));
    assert(!is_nice_1("haegwjzuvuyypxyu"));
    assert(!is_nice_1("dvszwmarrgswjxmb"));

    assert(is_nice_2("qjhvhtzxzqqjkmpb"));
    assert(is_nice_2("xxyxx"));
    assert(!is_nice_2("uurcxstgmygtbstg"));
    assert(!is_nice_2("ieodomkazucvgmuy"));
    auto lines = read_file_by_lines("input/day_5.txt");
    cout << "Part 1 answer: " << part_1(lines, is_nice_1) << "\n";
    cout << "Part 2 answer: " << part_1(lines, is_nice_2) << "\n";
    return 0;
}