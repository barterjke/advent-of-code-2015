#include "header.hpp"

std::unordered_map<string, int> wire_to_value;

std::optional<int> get(const string &s) {
    if (wire_to_value.contains(s)) return wire_to_value.at(s);
    try {
        return stoi(s);
    } catch (std::exception &e) {
        return {};
    }
}

void calc_knowns(const vector<string> &lines) {
    for (auto &line : lines) {
        auto s    = split(line, " ");
        auto wire = s.back();
        if (wire_to_value.contains(wire)) continue;
        switch (s.size()) {
        case 3:
            if (auto v = get(s[0])) {
                wire_to_value[wire] = *v;
            }
            break;
        case 4:
            assert(s[0] == "NOT");
            if (auto v = get(s[1])) {
                wire_to_value[wire] = ~(*v);
            }
            break;
        case 5:
            if (auto v1 = get(s[0]), v2 = get(s[2]); v1.has_value() && v2.has_value()) {
                if (s[1] == "OR")
                    wire_to_value[wire] = *v1 | *v2;
                else if (s[1] == "AND")
                    wire_to_value[wire] = *v1 & *v2;
                else if (s[1] == "LSHIFT")
                    wire_to_value[wire] = *v1 << *v2;
                else if (s[1] == "RSHIFT")
                    wire_to_value[wire] = *v1 >> *v2;
                else {
                    cout << endl << line << endl;
                    assert(0);
                }
            }
            break;
        default:
            cout << endl << "ERROR: " << s.size() << " " << line << endl;
            assert(0);
        }
    }
}

int part_1(const vector<string> &lines) {
    while (!wire_to_value.contains("a")) {
        calc_knowns(lines);
        // cout << wire_to_value << endl;
    }
    return wire_to_value.at("a");
}

int part_2(const vector<string> &lines) { 
    auto a = part_1(lines);
    wire_to_value.clear();
    wire_to_value["b"] = a;
    while (!wire_to_value.contains("a")) {
        calc_knowns(lines);
        // cout << wire_to_value << endl;
    }
    return wire_to_value.at("a");
 }

int main() {
    auto lines        = read_file_by_lines("input/day7.txt");
    auto part1_answer = part_1(lines);
    cout << "Part 1 answer " << part1_answer << "\n";
    auto part2_answer = part_2(lines);
    cout << "Part 2 answer " << part2_answer << "\n";
    return 0;
}