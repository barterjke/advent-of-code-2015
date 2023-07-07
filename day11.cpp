#include "header.hpp"

// Passwords must include one increasing straight of at least three letters, like abc, bcd, cde, and
// so on, up to xyz. They cannot skip letters; abd doesn't count. Passwords may not contain the
// letters i, o, or l, as these letters can be mistaken for other characters and are therefore
// confusing. Passwords must contain at least two different, non-overlapping pairs of letters, like
// aa, bb, or zz.

// 1. hijklmmn meets the first requirement (because it contains the straight hij) but fails the
// second requirement requirement (because it contains i and l).
// 2. abbceffg meets the third requirement
// (because it repeats bb and ff) but fails the first requirement.
// 3. abbcegjk fails the third requirement, because it only has one double letter (bb).
// The next password after abcdefgh is
// abcdffaa. The next password after ghijklmn is ghjaabcc, because you eventually skip all the
// passwords that start with ghi..., since i is not allowed.

bool is_good(const vector<char> &password) {
    char prev_c                  = 0;
    char first_paired_c          = 0;
    const char *minus_3_ptr      = password.data() - 3;
    bool contains_two_diff_pairs = false;
    bool increasing_straight     = false;
    int ind                      = 0;
    for (char c : password) {
        if (minus_3_ptr >= password.data()) {
            increasing_straight = increasing_straight || (*(minus_3_ptr + 1) - *minus_3_ptr == 1 &&
                                                          *(minus_3_ptr + 2) - *minus_3_ptr == 2);
        }
        if (c == 'i' || c == 'l' | c == 'o') return false;
        if (!contains_two_diff_pairs && c == prev_c) {
            int letter = c - 'a';
            if (first_paired_c == 0)
                first_paired_c = c;
            else if (first_paired_c != 0 && first_paired_c != c)
                contains_two_diff_pairs = true;
        }
        prev_c = c;
        minus_3_ptr++;
        ind++;
    }
    return contains_two_diff_pairs && increasing_straight;
}

bool is_good(const string &password) {
    return is_good(vector<char>(password.begin(), password.end()));
}

void plus_1(std::vector<char> &password, int index) {
    while (password[index] == 'z') {
        password[index] = 'a';
        index--;
        if (index < 0) {
            password.insert(password.begin(), 'a');
            index = password.size() - 1;
            return;
        }
    }
    password[index]++;
}

string part_1(const string &str, int offset = 0) {
    std::vector<char> password(str.begin(), str.end());
    int index = password.size() - 1;
    for (int i = 0; i < offset || !is_good(password); i++) {
        plus_1(password, index);
    }
    return string(password.begin(), password.end());
}

int main() {
    // they all fine just take precious time!

    // assert(!is_good("hijklmmn"));
    // assert(!is_good("abbceffg"));
    // assert(!is_good("abbceffg"));
    // assert(is_good("abcdffaa"));
    // assert(is_good("ghjaabcc"));
    // assert(part_1("abcdefgh") == "abcdffaa");
    // assert(part_1("ghijklmn") == "ghjaabcc");
    auto part1_answer = part_1("cqjxjnds");
    cout << "Part 1 answer " << part1_answer << "\n";
    cout << "Part 1 answer " << part_1(part1_answer, 1) << "\n";
    return 0;
}