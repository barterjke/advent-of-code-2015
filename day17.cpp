#include "header.hpp"
#include <cassert>
#include <functional>
#include <limits>
#include <numeric>

vector<int> append(vector<int> vec, int value) {
    vec.push_back(value);
    return vec;
}

int get_number_of_combinations_step(
    const vector<int> &numbers, const size_t step, const int sum,
    const int total, int &least_containers_used,
    int &number_of_combinations_with_least_container_used,
    const vector<int> combination) {
    if (sum == total) {
        if (combination.size() == least_containers_used)
            number_of_combinations_with_least_container_used++;
        if (combination.size() < least_containers_used) {
            least_containers_used = combination.size();
            number_of_combinations_with_least_container_used = 1;
        }
        return 1;
    }
    int number_of_combinations = 0;
    for (int i = step; i < numbers.size(); i++) {
        auto num = numbers[i];
        if (sum + num <= total)
            number_of_combinations += get_number_of_combinations_step(
                numbers, i + 1, sum + num, total, least_containers_used,
                number_of_combinations_with_least_container_used,
                append(combination, num));
    }
    return number_of_combinations;
}

std::pair<int, int>
get_number_of_combinations_with_the_same_sum(const vector<int> &numbers,
                                             int total) {

    int least_containers_used = std::numeric_limits<int>::max();
    int number_of_combinations_with_least_container_used = 0;
    auto number_of_combinations = get_number_of_combinations_step(
        numbers, 0, 0, total, least_containers_used,
        number_of_combinations_with_least_container_used, {});
    return {number_of_combinations,
            number_of_combinations_with_least_container_used};
}

vector<int> get_sorted_input() {
    auto str_numbers = read_file_by_lines("input/day_17.txt");
    vector<int> numbers;
    numbers.reserve(str_numbers.size());
    std::ranges::for_each(str_numbers,
                          [&numbers](auto x) { numbers.push_back(stoi(x)); });
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    return numbers;
}

int main() {
    auto test_result =
        get_number_of_combinations_with_the_same_sum({20, 15, 10, 5, 5}, 25);
    assert(test_result.first == 4 && test_result.second == 3);
    auto [first, second] =
        get_number_of_combinations_with_the_same_sum(get_sorted_input(), 150);
    print("Part 1 answer is", first);
    print("Part 2 answer is", second);
    return 0;
}