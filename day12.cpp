#include "header.hpp"
#include <regex>

int sum_numbers_in_json(const string &json) {
    int total = 0;
    std::regex number_regex("[-]?\\d+");   // Regular expression to match one or more digits
    for (std::sregex_iterator iterator(json.begin(), json.end(), number_regex), end;
         iterator != end; ++iterator) {
        std::smatch match = *iterator;
        total += std::stoi(match.str());
    }
    return total;
}

bool literal_is_red(const string &json, size_t &ind) {
    assert(json[ind++] == '"');
    std::array<char, 4> str_literal;
    str_literal[3]           = 0;
    size_t str_literal_index = 0;
    for (; ind < json.size(); ind++) {
        char c = json[ind];
        if (c == '"') {
            return str_literal_index == 3 && strcmp(str_literal.data(), "red") == 0;
        }
        if (str_literal_index < 3) str_literal[str_literal_index++] = c;
    }
    unreachable;
}

int parse_number(const string &json, size_t &ind) {
    int negative_factor = 1;
    int number          = 0;
    if (json[ind] == '-') {
        ind++;
        negative_factor = -1;
    }
    assert(isdigit(json[ind]));
    for (; ind < json.size(); ind++) {
        char c = json[ind];
        if (isdigit(c))
            number = number * 10 + (c - '0');
        else {
            ind--;
            return negative_factor * number;
        }
    }
    unreachable;
}

int sum_numbers_recursive(const string &json, size_t &ind) {
    int square_brackets_opened = 0;
    bool is_red                = false;
    int total                  = 0;
    for (; ind < json.size(); ++ind) {
        char c = json[ind];
        if (isspace(c) || c == ',' || c == ':') continue;
        switch (c) {
        case '[':
            square_brackets_opened++;
            break;
        case ']':
            square_brackets_opened--;
            break;
        case '"':
            is_red = (literal_is_red(json, ind) && square_brackets_opened == 0) || is_red;
            break;
        case '{':
            total += sum_numbers_recursive(json, ++ind);
            break;
        case '}':
            return is_red ? 0 : total;
        default:
            total += parse_number(json, ind);
        }
    }
    unreachable;
}

int sum_numbers_in_json_except_red(const string &json) {
    assert(json[0] == '{');
    size_t ind  = 1;
    auto result = sum_numbers_recursive(json, ind);
    assert(ind == json.size() - 1);
    return result;
}

int main() {
    string json       = read_entire_file("input/day_12.txt");
    auto part1_answer = sum_numbers_in_json(json);
    cout << "Part 1 answer " << part1_answer << "\n";
    auto part2_answer = sum_numbers_in_json_except_red(json);
    cout << "Part 2 answer " << part2_answer << "\n";
    return 0;
}