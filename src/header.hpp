#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>

#include <fstream>
#include <unordered_set>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <numeric>
#include <sstream>

using std::cout, std::vector, std::string, std::endl;

#define unreachable assert(0)

string qoute(const string &s) {
    std::stringstream ss;
    ss << std::quoted(s);
    return ss.str();
}

string read_entire_file(const string &path) {
    std::fstream ifs(path, std::ios::in | std::ios::binary | std::ios::ate);
    assert(ifs.is_open());
    auto file_size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    vector<char> bytes(file_size);
    ifs.read(bytes.data(), file_size);
    return string(bytes.data(), file_size);
}

vector<string> read_file_by_lines(const string &path) {
    std::fstream file(path);
    assert(file.is_open());
    string input;
    vector<string> result;
    while (std::getline(file, input)) {
        result.push_back(input);
    }
    return result;
}

vector<string> split(const string &s, const string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token     = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

template <typename T>
    requires std::is_signed_v<T>
string to_str(T t) {
    if (t == std::numeric_limits<T>::max()) return "MAX";
    if (t != 0 && t == std::numeric_limits<T>::min()) return "MIN";
    return std::to_string(t);
}

template <typename T>
    requires std::is_unsigned_v<T>
string to_str(T t) {
    if (t == std::numeric_limits<T>::max()) return "MAX";
    return "u" + std::to_string(t);
}

template <> string to_str(bool v) { return v ? "true" : "false"; }

template <> string to_str(char c) { return string() + c; }

template <typename T> string to_str(T *ptr) {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
}

template <> string to_str(float f) {
    std::stringstream ss;
    ss << f;
    auto result = ss.str();
    if (result.find(".") == string::npos && result.find("e") == string::npos) {
        return result + ".f";
    }
    return result + "f";
}

template <> string to_str(double d) {
    std::stringstream ss;
    ss << d;
    auto result = ss.str();
    if (result.find(".") == string::npos && result.find("e") == string::npos) {
        return result + ".d";
    }
    return result + "d";
}

string to_str(const string &s) { return s; }

string to_str(const char *c_str) { return c_str; }

template <class TupType, size_t... I>
string to_str(const TupType &_tup, std::index_sequence<I...>) {
    std::stringstream ss;
    (..., (ss << (I == 0 ? "t(" : ", ") << to_str(std::get<I>(_tup))));
    ss << ")";
    return ss.str();
}

template <class... T> string to_str(const std::tuple<T...> &_tup) {
    return to_str(_tup, std::make_index_sequence<sizeof...(T)>());
}

// template <typename Container>
// // requires(!std::is_same_v<Container, std::vector<bool>>)
// string to_str(const Container &container) {
//     std::stringstream ss;
//     ss << "container(";
//     size_t ind = 0;
//     for (auto element : container) {
//         ss << to_str(element) << (++ind == container.size() ? ')' : ' ');
//     }
//     return ss.str();
// }

// string to_str(const std::vector<bool> &container) {
//     std::stringstream ss;
//     ss << "bc(";
//     size_t ind = 0;
//     for (bool value : container) {
//         ss << to_str(value) << (++ind == container.size() ? ')' : ' ');
//     }
//     return ss.str();
// }

template <typename T> string to_str(const vector<T> &v) {
    std::stringstream ss;
    ss << "v[";
    for (auto &el : v) {
        ss << to_str(el);
        ss << (&el == &v.back() ? "]" : ", ");
    }
    return ss.str();
}

template <typename P1, typename P2> string to_str(const std::pair<P1, P2> &v) {
    std::stringstream ss;
    ss << "p(" << to_str(v.first) << ", " << to_str(v.second) << ")";
    return ss.str();
}

string to_str(const vector<string> &v) {
    std::stringstream ss;
    ss << "v[";
    for (const auto &el : v) {
        ss << std::quoted(el.substr(0, 50) + (el.size() > 50 ? ".." : ""))
           << (&el == &v.back() ? "]" : ", ");
    }
    return ss.str();
}

template <typename K, typename V> string to_str(const std::unordered_map<K, V> &m) {
    std::stringstream ss;
    ss << "{";
    auto i = 0;
    for (auto &[k, v] : m) {
        ss << to_str(k) << ": " << to_str(v) << (++i == m.size() ? "}" : ", ");
    }
    return ss.str();
}

template <typename K, typename V, typename H> string to_str(const std::unordered_map<K, V, H> &m) {
    std::stringstream ss;
    ss << "{";
    auto i = 0;
    for (auto &[k, v] : m) {
        ss << to_str(k) << ": " << to_str(v) << (++i == m.size() ? "}" : ", ");
    }
    return ss.str();
}

struct Vec2 {
    int x;
    int y;
    bool operator==(const Vec2 &rhs) const { return x == rhs.x && y == rhs.y; }
    struct HashFunction {
        size_t operator()(const Vec2 &point) const {
            return std::hash<int>()(point.x) + std::hash<int>()(point.y);
        }
    };
};

// string to_str(Vec2 v) { return "Vec2(" + to_str(v.x) + ", " + to_str(v.y) + ")"; }

template <typename... Args> string spaced(const Args &...args) {
    std::stringstream ss;
    (..., (ss << to_str(args) << ' '));
    return ss.str();
}

template <typename... Args> void print(const Args &...args) { cout << spaced(args...) << endl; }

void f_str(std::stringstream &ss, const string &str) { ss << str; }

template <typename T, typename... Args>
void f_str(std::stringstream &ss, const string &str, const T &first, const Args &...rest) {
    for (int i = 0; i < str.size(); ++i) {
        char c = str[i];
        if (c == '$') {
            ss << to_str(first);
            f_str(ss, str.substr(i + 1), rest...);
            break;
        } else
            ss << c;
    }
}

template <typename... Args> std::string formatted(const std::string &str, const Args &...args) {
    std::stringstream ss;
    f_str(ss, str, args...);
    return ss.str();
}

template <typename... Args> void format(const std::string &str, const Args &...args) {
    cout << formatted(str, args...) << endl;
}

struct HashFunction {
    size_t operator()(const std::tuple<string, string> &t) const {
        return std::hash<string>()(std::get<0>(t)) + std::hash<string>()(std::get<1>(t));
    }
};