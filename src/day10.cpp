#include "header.hpp"

string look_and_say(const std::string &s) {
    char prev_c  = 0;
    size_t count = 0;
    std::vector<char> result;
    for (char c : s) {
        if (prev_c != 0 && c != prev_c) {
            result.push_back('0' + count);
            result.push_back(prev_c);
            count = 0;
        }
        count++;
        prev_c = c;
    }
    result.push_back('0' + count);
    result.push_back(prev_c);
    return string(result.begin(), result.end());
}

string part_1(const std::string &s, int times) {
    string result = s;
    for (auto i = 0; i < times; i++) {
        result = look_and_say(result);
    }
    return result;
}

int main() {
    assert(look_and_say("111221") == "312211");
    assert(look_and_say("1211") == "111221");
    auto part1_string = part_1("3113322113", 40);
    cout << "Part 1 answer " << part1_string.size() << "\n";  
    cout << "Part 2 answer " << part_1(part1_string, 10).size() << "\n";
    return 0;
}