#include "header.hpp"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <numeric>
#include <vector>

vector<int> append(vector<int> vec, int value) {
    vec.push_back(value);
    return vec;
}

vector<int> get_package_weights_sorted() {
    auto lines = read_file_by_lines("input/day_24.txt");
    vector<int> numbers(lines.size());
    std::transform(lines.cbegin(), lines.cend(), numbers.begin(),
                   [](auto &s) { return stoi(s); });
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    return numbers;
}

struct PassData {
    const vector<int> &numbers;
    vector<vector<int>> results;
    size_t max_step;
    PassData(const vector<int> &numbers)
        : numbers(numbers), max_step(numbers.size()) {}
};

// breaks target into summands, using only numbers from PassData, and mind only
// the shortest one. for example, having numbers = [11, 9, 10, 5, 2, 3], target
// = 20, result will be [11, 9], and not [10, 5, 2, 3] result is stored in the
// PassData.result
void break_into_shortest_summands(PassData &data, int step, int target,
                                  vector<int> path) {
    if (step > data.max_step) return;
    if (target == 0) {
        data.max_step = step;
        data.results.push_back(path);
    }
    for (int i = step; i < data.numbers.size(); i++) {
        int num = data.numbers[i];
        if (num <= target)
            break_into_shortest_summands(data, i + 1, target - num,
                                         append(path, num));
    }
}

long get_smallest_quantum_entanglement(const vector<int> &package_weights,
                                       const int split_by) {
    int sum_wieght =
        std::accumulate(package_weights.begin(), package_weights.end(), 0);
    PassData data(package_weights);
    break_into_shortest_summands(data, 0, sum_wieght / split_by, {});
    long min_quantum_entanglement = std::numeric_limits<long>::max();
    for (const auto &result : data.results) {
        long quantum_entanglement = std::accumulate(
            result.cbegin(), result.cend(), 1l, std::multiplies<long>());
        min_quantum_entanglement = fmin(quantum_entanglement, min_quantum_entanglement);
    }
    return min_quantum_entanglement;
}

int main() {
    vector<int> package_weights = get_package_weights_sorted();
    print("Part 1 answer is",
          get_smallest_quantum_entanglement(package_weights, 3));
    print("Part 2 answer is",
          get_smallest_quantum_entanglement(package_weights, 4));
    return 0;
}