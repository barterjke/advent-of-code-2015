#include "header.hpp"

struct Elf {
    int number;
    int delta_time;
};

int naive_approach(const int N) {
    vector<Elf> elfs;
    vector<int> houses;
    int presents = 0;
    for (int i = 1; presents * 10 < N; i++) {
        elfs.push_back({i, 0});
        presents = 0;
        for (auto &elf : elfs) {
            if (elf.delta_time == 0) {
                elf.delta_time = elf.number;
                presents += elf.number;
            }
            elf.delta_time--;
        }
        houses.push_back(presents);
    }
    return houses.size();
}

int count_presents(int x) {
    int limit    = x;
    int presents = 0;
    if (x == 1) return 1;
    for (int i = 1; i < limit; ++i) {
        if (x % i == 0) {
            presents += i;
            limit = x / i;
            if (limit != i) {
                presents += limit;
            }
        }
    }
    return presents;
}

int count_presents_with_limits(int x) {
    int limit    = x;
    int presents = 0;
    if (x == 1) return 1;
    for (int i = 1; i < limit; ++i) {
        if (x % i == 0) {
            limit = x / i;
            if (limit <= 50) {
                presents += i;
            }
            if (limit != i && i <= 50) {
                presents += limit;
            }
        }
    }
    return presents;
}

int brute_force(auto count_function, int factor) {
    int i = 1000;
    while (count_function(i) * factor < 34000000) {
        i += 10;
    }
    i -= 100;
    while (count_function(i) * factor < 34000000) {
        i++;
    }
    return i;
}

int main() {
    print("Part 1 answer is", brute_force(count_presents, 10));
    print("Part 2 answer is", brute_force(count_presents_with_limits, 11));
    return 0;
}