#include "header.hpp"

enum type { OBJECT, STRING, NUMBER, ARRAY };

struct json_object {
    std::unordered_map<string, std::tuple<type, void *>> properties;
};

struct json_array {
    std::vector<std::tuple<type, void *>> values;
};

std::tuple<type, void *> parse_json(const string &json, size_t &ind);

std::tuple<type, void *> parse_string(const string &json, size_t &ind) {
    assert(json[ind++] == '"');
    vector<char> characters;
    for (; ind < json.size(); ind++) {
        char c = json[ind];
        if (c == '"') {
            auto str_ptr = new string(characters.begin(), characters.end());
            return {STRING, str_ptr};
        }
        characters.push_back(c);
    }
    unreachable;
}

std::tuple<type, void *> parse_number(const string &json, size_t &ind) {
    int number          = 0;
    int negative_factor = 1;
    for (; ind < json.size(); ind++) {
        char c = json[ind];
        if (c == '-') {
            negative_factor = -1;
            continue;
        }
        if (!isdigit(c)) {
            ind--;
            return {NUMBER, new int(negative_factor * number)};
        }
        number = number * 10 + (c - '0');
    }
    unreachable;
}

std::tuple<type, void *> parse_array(const string &json, size_t &ind) {
    auto arr_ptr = new json_array;
    assert(json[ind++] == '[');
    for (; ind < json.size(); ind++) {
        char c = json[ind];
        if (isspace(c) || c == ',') continue;
        if (c == ']') return {ARRAY, arr_ptr};
        auto data = parse_json(json, ind);
        arr_ptr->values.push_back(data);
    }
    unreachable;
}

std::tuple<type, void *> parse_obj(const string &json, size_t &ind) {
    auto obj_ptr = new json_object;
    string property;
    assert(json[ind++] == '{');
    for (; ind < json.size(); ind++) {
        char c = json[ind];
        if (isspace(c)) continue;
        if (c == ',')
            assert(obj_ptr->properties.size() != 0 && property.empty());
        else if (c == '}')
            return {OBJECT, obj_ptr};
        else if (c == ':') {
            assert(!property.empty());
            auto data = parse_json(json, ++ind);
            obj_ptr->properties.insert({property, data});
            property.clear();
        } else if (c == '"') {
            assert(property.empty());
            auto [type, ptr] = parse_string(json, ind);
            string *str_ptr  = static_cast<std::string *>(ptr);
            property         = *str_ptr;
            delete str_ptr;
        } else {
            cout << c;
            unreachable;
        }
    }
    unreachable;
}

std::tuple<type, void *> parse_json(const string &json, size_t &ind) {
    char c = json[ind];
    if (c == '{') return parse_obj(json, ind);
    if (c == '"') return parse_string(json, ind);
    if (c == '[') return parse_array(json, ind);
    if (isdigit(c) || c == '-') return parse_number(json, ind);
    unreachable;
}

int sum_numbers_in_json(const std::tuple<type, void *> &json, bool ignore_red = false) {
    auto total       = 0;
    auto [type, ptr] = json;
    switch (type) {
    case OBJECT: {
        auto obj_ptr = (json_object *)ptr;
        for (auto &[k, v] : obj_ptr->properties) {
            if (ignore_red && std::get<0>(v) == STRING && *(string *)std::get<1>(v) == "red")
                return 0;
            total += sum_numbers_in_json(v, ignore_red);
        }
        return total;
    }
    case ARRAY: {
        auto obj_ptr = (json_array *)ptr;
        for (auto &v : obj_ptr->values) {
            total += sum_numbers_in_json(v, ignore_red);
        }
        return total;
    }
    case NUMBER:
        return *(int *)(ptr);
    case STRING:
        return 0;
    }
}

const unsigned int OFFSET_LENGTH = 4;

void pretty_print(std::stringstream &ss, const std::tuple<type, void *> &json, int offset = 0) {
    auto [type, ptr] = json;
    auto offset_str  = string(offset, ' ');
    auto extra       = string(offset + OFFSET_LENGTH, ' ');
    switch (type) {
    case OBJECT: {
        auto obj_ptr = (json_object *)ptr;
        ss << "{" << endl;
        for (auto &[k, v] : obj_ptr->properties) {
            ss << extra << k << ": ";
            pretty_print(ss, v, offset + OFFSET_LENGTH);
            ss << "," << endl;
        }
        ss << offset_str << "}";
        return;
    }
    case ARRAY: {
        ss << "[" << endl;
        auto arr_ptr = (json_array *)ptr;
        for (auto &v : arr_ptr->values) {
            ss << extra;
            pretty_print(ss, v, offset + OFFSET_LENGTH);
            ss << "," << endl;
        }
        ss << offset_str << "]";
        return;
    }
    case NUMBER:
        ss << *(int *)(ptr);
        return;
    case STRING:
        ss << *(std::string *)ptr;
        return;
    }
}

void free(const std::tuple<type, void *> &json) {
    auto [type, ptr] = json;
    switch (type) {
    case OBJECT: {
        auto obj_ptr = (json_object *)ptr;
        for (auto &[k, v] : obj_ptr->properties) {
            free(v);
        }
        delete obj_ptr;
        return;
    }
    case ARRAY: {
        auto arr_ptr = (json_array *)ptr;
        for (auto &v : arr_ptr->values) {
            free(v);
        }
        delete arr_ptr;
        return;
    }
    case NUMBER:
        delete (int *)(ptr);
        return;
    case STRING:
        delete (std::string *)ptr;
        return;
    }
}

std::ostream &operator<<(std::ostream &os, const std::tuple<type, void *> &json) {
    std::stringstream ss;
    pretty_print(ss, json);
    return os << ss.str();
}

int main() {
    string str = read_entire_file("input/day_12.txt");
    size_t ind = 0;
    auto data  = parse_json(str, ind);
    cout << data;
    cout << "Part 1 answer " << sum_numbers_in_json(data) << endl;
    cout << "Part 2 answer " << sum_numbers_in_json(data, true) << endl;
    free(data);
    return 0;
}