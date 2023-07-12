#include "header.hpp"
#include <array>
#include <functional>
#include <numeric>
#include <vector>

string without_last(const string &str) { return str.substr(0, str.size() - 1); }

vector<std::array<int, 5>> process_input(const vector<string> &lines) {
    vector<std::array<int, 5>> weights;
    for (auto line : lines) {
        auto s         = split(line, " ");
        auto name      = without_last(s[0]);
        int capacity   = stoi(without_last(s[2]));
        int durability = stoi(without_last(s[4]));
        int flavor     = stoi(without_last(s[6]));
        int texture    = stoi(without_last(s[8]));
        int calories   = stoi(s[10]);
        weights.push_back({capacity, durability, flavor, texture, calories});
    }
    return weights;
}

int sum_recursive(const auto &items, int step) {
    if (step < 0) return 0;
    if (step == 0) return items[0];
    return items[step] + sum_recursive(items, step - 1);
}

template <typename Container>
int iter_recursive(vector<Container> weights, auto &items, int step, bool limit_calories = false) {
    if (step == items.size()) {
        step--;
        if (std::accumulate(items.begin(), items.end(), 0) != 100) return 0;
        Container total = {0, 0, 0, 0};
        for (; step >= 0; step--) {
            for (int i = 0; i < weights[step].size(); i++) {
                total[i] += items[step] * weights[step][i];
                if (step == 0 && total[i] <= 0) return 0;
            }
        }
        if (limit_calories && total[total.size() - 1] != 500) return 0;
        return std::accumulate(total.begin(), total.end() - 1, 1, std::multiplies<int>());
    }
    int max = 0;
    for (items[step] = 0; items[step] <= 100 - sum_recursive(items, step - 1); items[step]++) {
        max = fmax(max, iter_recursive(weights, items, step + 1, limit_calories));
    }
    return max;
}

int highest_scoring_cookie_generic(const vector<string> &lines, bool limit_calories = false) {
    auto weights = process_input(lines);
    std::array<int, 4> items;
    return iter_recursive(weights, items, 0, limit_calories);
}

int highest_scoring_cookie_specific(const vector<string> &lines, bool no_limit_callories = true) {
    auto weights = process_input(lines);
    int max      = 0;
    // Sprinkles at least 1
    // Butterscotch at least 1/5 + 1 of candy
    // Chocolate at least (5/2 Sprinkles + 5/3 Butterscotch)+1
    // Candy at least 1/5 + 1 of Chocolate

    // s >= 1
    // b >= (ca/5) + 1
    // ch >= max(2/5s, 3/5b) + 1
    // ca >= (ch/5) + 1
    for (int s = 1; s <= 100; s++) {
        for (int ca = 0; ca <= 100 - s; ca++) {
            for (int b = (ca / 5) + 1; b <= 100 - s - ca; b++) {
                for (int ch = fmax(2 / 5 * s, 3 / 5 * b) + 1;
                     ch <= fmin(5 * ca - 5, 100 - s - ca - b); ch++) {
                    if (!(s + ca + b + ch == 100 &&
                          (no_limit_callories || s * weights[0][4] + b * weights[1][4] +
                                                         ch * weights[2][4] + ca * weights[3][4] ==
                                                     500)))
                        continue;
                    std::array<int, 4> total;
                    for (int i = 0; i < total.size(); i++)
                        total[i] = fmax(s * weights[0][i] + b * weights[1][i] + ch * weights[2][i] +
                                            ca * weights[3][i],
                                        0);
                    max = fmax(total[0] * total[1] * total[2] * total[3], max);
                }
            }
        }
    }
    return max;
}

int main() {
    auto lines = read_file_by_lines("input/day_15.txt");
    format("Part 1 generic answer: $", highest_scoring_cookie_generic(lines));
    format("Part 2 generic answer: $", highest_scoring_cookie_generic(lines, true));

    format("Part 1 specific answer: $", highest_scoring_cookie_specific(lines, true));
    format("Part 2 specific answer: $", highest_scoring_cookie_specific(lines, false));
    return 0;
}
