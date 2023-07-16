#include "header.hpp"
#include <functional>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

const int TOTAL = 150;
struct Num {
    int x;
    struct hash {
        size_t operator()(const vector<Num> &nums) {
            return std::accumulate(nums.begin(), nums.end(), 0, [](auto acc, auto num) {
                return std::hash<int>()(acc) + std::hash<int>()(num.x);
            });
        }
    };
};

std::unordered_set<std::vector<Num()>>

    void rec(vector<int> numbers, vector<int> result, int step = 0) {
    if (step == numbers.size()) {
        return;
    }
    for (int i = 0; i < numbers.size(); i++) {
        auto num = numbers[i];
        if (num == 0) continue;
        numbers[i]   = 0;
        result[step] = num;
        int sum      = std::accumulate(result.begin(), result.end(), 0);
        if (sum == TOTAL) {
            print(result);
            continue;
        } else if (sum > TOTAL) {
            continue;
        } else {
            rec(numbers, result, step + 1);
        }
        numbers[i] = num;
    }
}

int main() {
    auto str_numbers = split(read_entire_file("input/day_17.txt"), "\n");
    vector<int> numbers;
    numbers.reserve(str_numbers.size());
    std::ranges::for_each(str_numbers, [&numbers](auto x) { numbers.push_back(stoi(x)); });
    print(numbers);
    // print(get_combinations(numbers.size()));
    // rec({20, 15, 10, 5, 5});
    vector<int> result(20);
    rec(numbers, result);
    // print(result);
    return 0;
}