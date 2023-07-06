#include "header.hpp"
#include "md5.h"

int part_1(const string input) {
    for (auto i = 1;; ++i) {
        if (auto hash = md5(input + std::to_string(i)); hash.substr(0, 5) == "00000") {
            return i;
        }
    }
}

int part_2(const string input, int start) {
    for (auto i = start;; ++i) {
        if (auto hash = md5(input + std::to_string(i)); hash.substr(0, 6) == "000000") {
            return i;
        }
    }
}

int main() {
    auto result_1 = part_1("ckczppom");
    cout << "Part 1 answer: " << result_1 << "\n";
    cout << "Part 2 answer: " << part_2("ckczppom", result_1) << "\n";
    return 0;
}