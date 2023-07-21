#include "header.hpp"

int get_code(const int row, const int column) {
    std::vector<long> codes = {20151125};
    int x                   = 1;
    int y                   = 1;
    int current_diagonal    = 1;
    for (int i = 1;; i++) {
        x++;
        y--;
        if (x > current_diagonal) {
            x = 1;
            y = ++current_diagonal;
        }
        codes.push_back(codes[i - 1] * 252533 % 33554393);
        if (x == column && y == row) return codes[i];
    }
}

int main() {
    cout << get_code(2978, 3083) << endl;
    return 0;
}