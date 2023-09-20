#include "header.hpp"
#include <cassert>

int find_fastest_rocket(const vector<string> &lines, int total_seconds) {
    // Dancer can fly 27 km/s for 5 seconds, but then must rest for 132 seconds.
    int max_distance = 0;
    for (auto &line : lines) {
        auto s         = split(line, " ");
        auto speed     = stoi(s[3]);
        auto time      = stoi(s[6]);
        auto cd        = stoi(s[13]);
        int whole_secs = total_seconds / (time + cd);
        int distance =
            speed * (time * whole_secs + fmin(total_seconds - (time + cd) * whole_secs, time));
        max_distance = fmax(distance, max_distance);
    }
    return max_distance;
}

struct RocketData {
    int speed;
    int time;
    int cd;
    int current_time;
    int distance = 0;
    int score    = 0;
    bool resting = false;
    RocketData(int speed, int time, int cd)
        : speed(speed), time(time), cd(cd), current_time(time) {}
    void step() {
        if (!resting) distance += speed;
        current_time--;
        if (current_time == 0) {
            resting      = !resting;
            current_time = resting ? cd : time;
        }
    }
};

int find_leading_rocket(const vector<string> &lines, int total_seconds, bool by_distance = false) {
    // Dancer can fly 27 km/s for 5 seconds, but then must rest for 132 seconds.
    int i = 0;
    vector<RocketData> rockets;
    rockets.reserve(lines.size());
    for (auto &line : lines) {
        auto s     = split(line, " ");
        auto speed = stoi(s[3]);
        auto time  = stoi(s[6]);
        auto cd    = stoi(s[13]);
        rockets.emplace_back(speed, time, cd);
    }
    for (int i = 0; i < total_seconds; i++) {
        int max_distance = 0;
        for (auto &rocket : rockets) {
            rocket.step();
            if (rocket.distance >= max_distance) {
                max_distance = rocket.distance;
            }
        }
        for (auto &rocket : rockets) {
            if (rocket.distance == max_distance) rocket.score++;
        }
    }
    auto max = 0;
    for (auto &rocket : rockets) {
        max = fmax(by_distance ? rocket.distance : rocket.score, max);
    }
    return max;
}

int main() {
    auto test_lines = read_file_by_lines("input/day_14_0.txt");
    assert(find_fastest_rocket(test_lines, 1000) == 1120 &&
           find_leading_rocket(test_lines, 1000, true) == 1120);
    assert(find_leading_rocket(test_lines, 1000) == 689);

    auto lines = read_file_by_lines("input/day_14.txt");
    print("Part 1 answer", find_fastest_rocket(lines, 2503));
    print("Part 2 answer", find_leading_rocket(lines, 2503));
}