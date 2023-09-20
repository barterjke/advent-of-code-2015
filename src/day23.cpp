#include "header.hpp"

// hlf r sets register r to half its current value, then continues with the next instruction.
// tpl r sets register r to triple its current value, then continues with the next instruction.
// inc r increments register r, adding 1 to it, then continues with the next instruction.
// jmp offset is a jump; it continues with the instruction offset away relative to itself.
// jie r, offset is like jmp, but only jumps if register r is even ("jump if even").
// jio r, offset is like jmp, but only jumps if register r is 1 ("jump if one", not odd).
void execute(const vector<string> &code, int *a, int *b) {
    int *reg;
    for (int i = 0; i < code.size(); i++) {
        auto instruction = split(code[i], " ");
        auto cmd         = instruction[0];
        if (cmd == "hlf" || cmd == "tpl" || cmd == "inc") reg = instruction[1] == "a" ? a : b;
        if (cmd == "hlf") *reg /= 2;
        if (cmd == "tpl") *reg *= 3;
        if (cmd == "inc") (*reg)++;
        if (cmd == "jmp") i += stoi(instruction[1]) - 1;
        if (cmd == "jie" || cmd == "jio") reg = instruction[1][0] == 'a' ? a : b;
        if (cmd == "jie" && *reg % 2 == 0) i += stoi(instruction[2]) - 1;
        if (cmd == "jio" && *reg == 1) i += stoi(instruction[2]) - 1;
    }
}

int main() {
    auto code = read_file_by_lines("input/day_23.txt");
    int a = 0, b = 0;
    execute(code, &a, &b);
    print("Part 1 answer is", b);
    a = 1, b = 0;
    execute(code, &a, &b);
    print("Part 1 answer is", b);
    return 0;
}