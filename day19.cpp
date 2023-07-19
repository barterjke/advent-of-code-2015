#include "header.hpp"

int main() {
    auto lines = read_file_by_lines("input/day_19.txt");
    std::unordered_map<string, std::vector<string>> replacements;
    for (auto &line : lines) {
        if (line == "") break;
        auto s      = split(line, "=>");
        auto before = s[0].substr(0, s[0].size() - 1);
        auto after  = s[1].substr(1);
        if (replacements.contains(before)) {
            replacements.at(before).push_back(after);
        } else {
            replacements[before] = {after};
        }
    }
    vector<string> moleculas;
    string current_molecula;
    for (char c : lines.back()) {
        if (isupper(c) && !current_molecula.empty()) {
            moleculas.push_back(current_molecula);
            current_molecula.clear();
            current_molecula = string() + c;
        } else {
            current_molecula += c;
        }
    }
    if (!current_molecula.empty()) moleculas.push_back(current_molecula);
    std::unordered_set<string> results;
    for (auto &molecula : moleculas) {
        auto before = molecula;
        print(molecula);
        for (auto after : replacements[molecula]) {
            molecula        = after;
            auto joined_str = std::accumulate(moleculas.begin(), moleculas.end(), string(),
                                              [](auto acc, auto x) { return std::move(acc) + x; });
            results.insert(joined_str);
        }
        molecula = before;
    }
    // print(replacements);
    // print(results);
    print(results.size());
    return 0;
}