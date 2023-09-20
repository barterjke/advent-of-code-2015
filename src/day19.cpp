#include "header.hpp"
#include <cassert>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

void fill(std::unordered_map<string, std::vector<string>> &replacements,
          vector<string> &moleculas) {
    auto lines = read_file_by_lines("input/day_19.txt");
    for (auto &line : lines) {
        if (line == "") break;
        auto s      = split(line, "=>");
        auto before = s[0].substr(0, s[0].size() - 1);
        auto after  = s[1].substr(1);
        if (replacements.contains(before)) {
            replacements.at(before).push_back(after);
        } else {
            replacements[before] = {after};
        }
    }

    string current_molecula;
    for (char c : lines.back()) {
        if (isupper(c) && !current_molecula.empty()) {
            moleculas.push_back(current_molecula);
            current_molecula.clear();
            current_molecula = string() + c;
        } else {
            current_molecula += c;
        }
    }
    if (!current_molecula.empty()) moleculas.push_back(current_molecula);
}

int f(vector<string> moleculas,
      std::unordered_map<string, std::vector<string>> replacements) {
    std::unordered_set<string> results;
    for (auto &molecula : moleculas) {
        auto before = molecula;
        for (const auto &after : replacements[molecula]) {
            molecula        = after;
            auto joined_str = std::accumulate(
                moleculas.begin(), moleculas.end(), string(),
                [](const string &acc, const string &x) { return acc + x; });
            results.insert(joined_str);
        }
        molecula = before;
    }
    return results.size();
}

string replace(std::string str, const std::string &from,
               const std::string &to) {
    size_t start_pos = str.find(from);
    assert(start_pos != std::string::npos);
    str.replace(start_pos, from.length(), to);
    return str;
}

string target_molecula =
    "CRnCaSiRnBSiRnFArTiBPTiTiBFArPBCaSiThSiRnTiBPBPMgArCaSiRnTiMgArCaSiThCaSiR"
    "nFArRnSiRnFArTiTiBFArCaCaSiRnSiThCaCaSiRnMgArFYSiRnFYCaFArSiThCaSiThPBPTiM"
    "gArCaPRnSiAlArPBCaCaSiRnFYSiThCaRnFArArCaCaSiRnPBSiRnFArMgYCaCaCaCaSiThCaC"
    "aSiAlArCaCaSiRnPBSiAlArBCaCaCaCaSiThCaPBSiThPBPBCaSiRnFYFArSiThCaSiRnFArBC"
    "aCaSiRnFYFArSiThCaPBSiThCaSiRnPMgArRnFArPTiBCaPRnFArCaCaCaCaSiRnCaCaSiRnFY"
    "FArFArBCaSiThFArThSiThSiRnTiRnPMgArFArCaSiThCaPBCaSiRnBFArCaCaPRnCaCaPMgAr"
    "SiRnFYFArCaSiThRnPBPMgAr";

bool dfs(string current_molecula,
         const std::unordered_map<string, std::vector<string>> &replacements) {
    if (current_molecula == target_molecula) return true;
    if (current_molecula.size() > target_molecula.size()) return false;
    for (auto &[k, vec] : replacements) {
        if (current_molecula.find(k) != string::npos) {
            for (auto replacement : vec) {
                string news = replace(current_molecula, k, replacement);
                print(news);
                bool maybe = dfs(news, replacements);
                if (maybe) return true;
            }
        }
    }
    return false;
}

std::unordered_set<string> visited;

int lev(string a, string b) {
    if (b.empty()) return a.size();
    if (a.empty()) return b.size();
    if (a[0] == b[0]) return lev(a.substr(1), b.substr(1));
    return 1 + fmin(fmin(lev(a.substr(1), b), lev(a, b.substr(1))),
                    lev(a.substr(1), b.substr(1)));
}

int OSA(string s, string t) {
    int n = s.size();
    int m = t.size();
    int d1, d2, d3, cost;
    vector<vector<int>> d(n + 2, vector<int>(m + 2));
    for (int i = 0; i < n + 1; i++)
        d[i][0] = i;
    for (int j = 1; j < m + 1; j++)
        d[0][j] = j;
    int i, j;
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= m; j++) {
            if (s[i + 1] == t[j + 1])
                cost = 0;
            else
                cost = 1;
            d1              = d[i][j + 1] + 1;
            d2              = d[i + 1][j] + 1;
            d3              = d[i][j] + cost;
            d[i + 1][j + 1] = fmin(d1, fmin(d2, d3));
            if (i > 0 && j > 0 && s[i] == t[j - 1] &&
                s[i - 1] == t[j])   // transposition
            {
                d[i + 1][j + 1] = fmin(d[i + 1][j + 1], d[i - 1][j - 1] + cost);
            }
        }
    }
    return d[n + 1][m + 1];
}

bool dfs_reversed(string current_molecula,
                  const std::unordered_map<string, string> &replacements) {
    if (visited.contains(current_molecula)) return false;
    visited.insert(current_molecula);
    if (current_molecula == "e") return true;
    for (auto &[from, to] : replacements) {
        if (from != current_molecula && to == "e") continue;
        if (current_molecula.find(from) != string::npos) {
            string news = replace(current_molecula, from, to);
            print(news);
            bool maybe = dfs_reversed(news, replacements);
            if (maybe) return true;
        }
    }
    return false;
}

#define d(i, j)          dd[(i) * (m + 2) + (j)]
#define min(x, y)        ((x) < (y) ? (x) : (y))
#define min3(a, b, c)    ((a) < (b) ? min((a), (c)) : min((b), (c)))
#define min4(a, b, c, d) ((a) < (b) ? min3((a), (c), (d)) : min3((b), (c), (d)))

int dldist2(string s, string t) {
    int n = s.size();
    int m = t.size();
    int *dd;
    int i, j, cost, i1, j1, DB;
    int INF = n + m;
    int DA[256 * sizeof(int)];

    memset(DA, 0, sizeof(DA));

    if (!(dd = (int *)malloc((n + 2) * (m + 2) * sizeof(int)))) {
        return -1;
    }

    d(0, 0) = INF;
    for (i = 0; i < n + 1; i++) {
        d(i + 1, 1) = i;
        d(i + 1, 0) = INF;
    }
    for (j = 0; j < m + 1; j++) {
        d(1, j + 1) = j;
        d(0, j + 1) = INF;
    }

    for (i = 1; i < n + 1; i++) {
        DB = 0;
        for (j = 1; j < m + 1; j++) {
            i1   = DA[t[j - 1]];
            j1   = DB;
            cost = ((s[i - 1] == t[j - 1]) ? 0 : 1);
            if (cost == 0) DB = j;
            d(i + 1, j + 1) =
                min4(d(i, j) + cost, d(i + 1, j) + 1, d(i, j + 1) + 1,
                     d(i1, j1) + (i - i1 - 1) + 1 + (j - j1 - 1));
        }
        DA[s[i - 1]] = i;
    }
    cost = d(n + 1, m + 1);
    free(dd);
    return cost;
}

using str_and_distance = std::pair<string, int>;
auto cmp               = [](str_and_distance left, str_and_distance right) {
    return left.first.size() > right.first.size();
};
std::priority_queue<str_and_distance, std::vector<str_and_distance>,
                    decltype(cmp)>
    queue(cmp);

vector<string> append(vector<string> vec, string value) {
    vec.push_back(value);
    return vec;
}

int calculate_shortest_transformation(
    std::unordered_map<string, string> reversed_replacements) {
    queue.push({target_molecula, 0});
    while (!queue.empty()) {
        auto [current_molecula, steps] = queue.top();
        if (current_molecula == "e") return steps;
        queue.pop();
        for (auto [from, to] : reversed_replacements) {
            if (current_molecula.find(from) != string::npos) {
                auto news = replace(current_molecula, from, to);
                queue.push({news, steps + 1});
            }
        }
    }
    return -1;
}

int main() {
    std::unordered_map<string, std::vector<string>> replacements;
    vector<string> moleculas;
    fill(replacements, moleculas);
    print("Part 1 answer is", f(moleculas, replacements));
    std::unordered_map<string, string> reversed_replacements;
    for (auto &[k, vec] : replacements) {
        for (auto &v : vec) {
            assert(!reversed_replacements.contains(v));
            reversed_replacements[v] = k;
        }
    }
    print("Part 2 answer is",
          calculate_shortest_transformation(reversed_replacements));
    return 0;
}