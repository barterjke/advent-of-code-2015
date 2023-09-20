#include <iostream>
#include "header.hpp"
#include <vector>

void generateCombinations(const std::vector<int>& elements, int k) {
    int n = elements.size();
    int combinations = 1 << n;

    for (int i = 0; i < combinations; i++) {
        if (__builtin_popcount(i) == k) { // Count the number of set bits
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    std::cout << elements[j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

std::vector<int> get_sorted_input() {
    auto str_numbers = read_file_by_lines("input/day_17.txt");
    vector<int> numbers;
    numbers.reserve(str_numbers.size());
    std::ranges::for_each(str_numbers,
                          [&numbers](auto x) { numbers.push_back(stoi(x)); });
    return numbers;
}

int main() {
    generateCombinations(get_sorted_input(), 20);

    return 0;
}