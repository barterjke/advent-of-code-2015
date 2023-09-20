#include "header.hpp"
#include <list>

int f(const std::vector<std::string> &lines) {
    for (auto &line : lines) {
    }
    return 0;
}

int main() {
    auto lines = read_file_by_lines("input/day_7.txt");
    // print(lines);
    // auto part1_answer                   = f(lines);
    auto min                                 = INT16_MIN;
    unsigned int ui                          = 18;
    std::unordered_map<std::string, int> map = {{"a", 3}, {"b", 18}};
    string s                                 = "hahah";
    cout << formatted("$ Answer for part $ is: $", s, 1, vector{3, 2}) << endl;
    format("hello $ world $", "fucking", 42);
    print(s);
    print(min, false, 1);
    print(2.0000015f, 2.0000015, "are very small");
    print(1e-09, 1e-40, 1e+40);
    print(ui, 3.2, Vec2{3, 5});
    print(map, vector{19, 18, 32});
    print('?', std::list{2, 18, 19});
    size_t i = 0;
    auto t   = std::numeric_limits<size_t>::max();
    print(3, 5.0f, --i, t, "sss", &i);
    print(std::make_tuple(3, 5.0f, i, t, "sss", &i));
    print("list", std::list{'a', 'b', 'c'}, "; array", std::array{2, 18, 19}, '?');
    print(vector{true, false});
    print(true, "is not", false);
    for (bool s : vector{false, true}) {
        print(s);
    }
    return 0;
}