#include "header.hpp"
#include <array>
#include <cstring>

const int SIZE = 100;

bool get_or_default(const std::array<std::array<bool, SIZE>, SIZE> &grid, const int x,
                    const int y) {
    return (x >= SIZE || x < 0 || y >= SIZE || y < 0) ? false : grid.at(x).at(y);
}

int count_neighbors_on(const std::array<std::array<bool, SIZE>, SIZE> &grid, const int x,
                       const int y) {
    int counter = 0;
    for (auto i = -1; i <= 1; i++) {
        for (auto j = -1; j <= 1; j++) {
            counter += !(i == j && i == 0) && get_or_default(grid, x + i, y + j);
        }
    }
    return counter;
}

void print(const std::array<std::array<bool, SIZE>, SIZE> &grid) {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            cout << (grid[x][y] ? '#' : '.');
        }
        cout << endl;
    }
    cout << "------------------" << endl;
}

void iterate_once(std::array<std::array<bool, SIZE>, SIZE> &grid, bool corners_always_on) {
    std::array<std::array<bool, SIZE>, SIZE> grid_after_move;
    memcpy(&grid_after_move[0][0], &grid[0][0], sizeof(grid));
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            bool is_corner = (x == SIZE - 1 && y == SIZE - 1) || (x == SIZE - 1 && y == 0) ||
                             (y == SIZE - 1 && x == 0) || (x == 0 && y == 0);
            if (corners_always_on && is_corner) {
                continue;
            }
            int neighbors_on_counter = count_neighbors_on(grid, x, y);
            // A light which is on stays on when 2 or 3 neighbors are on, and turns off otherwise.
            // A light which is off turns on if exactly 3 neighbors are on, and stays off otherwise.
            if (grid[x][y])
                grid_after_move[x][y] = neighbors_on_counter == 2 || neighbors_on_counter == 3;
            else
                grid_after_move[x][y] = neighbors_on_counter == 3;
        }
    }
    memcpy(&grid[0][0], &grid_after_move[0][0], sizeof(grid));
}

std::array<std::array<bool, SIZE>, SIZE> get_grid(const vector<string> &lines) {
    std::array<std::array<bool, SIZE>, SIZE> grid = {0};
    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines[y].size(); x++) {
            grid[x][y] = lines[y][x] == '#';
        }
    }
    return grid;
}

int count_lights_on(std::array<std::array<bool, SIZE>, SIZE> grid, bool corners_always_on = false) {
    if (corners_always_on) {
        grid[SIZE - 1][0]        = true;
        grid[SIZE - 1][SIZE - 1] = true;
        grid[0][SIZE - 1]        = true;
        grid[0][0]               = true;
    }
    for (int i = 0; i < 100; i++) {
        // print(grid);
        iterate_once(grid, corners_always_on);
    }
    int lights_on_counter = 0;
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            lights_on_counter += grid[x][y];
        }
    }
    return lights_on_counter;
}

int main() {
    auto lines = read_file_by_lines("input/day_18.txt");
    auto grid = get_grid(lines);
    print("Part 1 answer is:", count_lights_on(grid));
    print("Part 2 answer is:", count_lights_on(grid, true));
    return 0;
}