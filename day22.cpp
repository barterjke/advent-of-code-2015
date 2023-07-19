#include "header.hpp"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <regex>

vector<int> get_all_integers(const string &str) {
    std::regex number_regex("[-]?\\d+");
    vector<int> numbers;
    for (std::sregex_iterator iterator(str.begin(), str.end(), number_regex), end; iterator != end;
         ++iterator) {
        std::smatch match = *iterator;
        numbers.push_back(std::stoi(match.str()));
    }
    return numbers;
}

struct Boss {
    int health;
    int damage;
};

struct Hero {
    int health        = 50;
    int mana          = 500;
    int armor         = 0;
    int shield_time   = 0;
    int poison_time   = 0;
    int recharge_time = 0;
};

enum Ability { MAGIC_MISSLE, DRAIN, SHIELD, RECHARGE, POISON };

// Magic Missile costs 53 mana. It instantly does 4 damage.

// Drain costs 73 mana. It instantly does 2 damage and heals you for 2 hit points.

// Shield costs 113 mana. It starts an effect that lasts for 6 turns. While it is active, your armor
// is increased by 7.

// Poison costs 173 mana. It starts an effect that lasts for 6 turns. At the start of each turn
// while it is active, it deals the boss 3 damage.

// Recharge costs 229 mana. It starts an effect that lasts for 5 turns. At the start of each turn
// while it is active, it gives you 101 new mana.

bool activate_ability(Ability ability, Hero &hero, Boss &boss, int &mana_spent) {
    switch (ability) {
    case MAGIC_MISSLE:
        mana_spent += 53;
        hero.mana -= 53;
        boss.health -= 4;
        break;
    case DRAIN:
        mana_spent += 73;
        hero.mana -= 73;
        hero.health += 2;
        boss.health -= 2;
    case SHIELD:
        if (hero.shield_time > 0) return false;
        mana_spent += 113;
        hero.mana -= 113;
        hero.shield_time = 6;
        break;
    case POISON:
        if (hero.poison_time > 0) return false;
        mana_spent += 173;
        hero.mana -= 173;
        hero.poison_time = 6;
        break;
    case RECHARGE:
        if (hero.recharge_time > 0) return false;
        mana_spent += 229;
        hero.mana -= 229;
        hero.recharge_time = 5;
    }
    return hero.mana >= 0;
}

void start_turn(Hero &hero, Boss &boss) {
    hero.armor = 0;
    if (hero.poison_time-- > 0) boss.health -= 3;
    if (hero.recharge_time-- > 0) hero.mana += 101;
    if (hero.shield_time-- > 0) hero.armor = 7;
}

void boss_attack(Boss &boss, Hero &hero) { hero.health -= fmax(boss.damage - hero.armor, 1); }

constexpr auto min(const auto &head0, const auto &head1, const auto &...tail) {
    if constexpr (sizeof...(tail) == 0) {
        return head0 < head1 ? head0 : head1;
    } else {
        return min(min(head0, head1), tail...);
    }
}

int choose_ability(Hero hero, Boss boss, int mana_spent, bool hard_mode);

int fight_recursive(Ability ability, Hero hero, Boss boss, int mana_spent, bool hard_mode) {
    if (hard_mode && --hero.health <= 0)
        return INT16_MAX;                      // if hardmode player loses hp before everything
    start_turn(hero, boss);                    // start player's turn
    if (boss.health <= 0) return mana_spent;   // if boss died because of poison
    if (!activate_ability(ability, hero, boss, mana_spent))
        return INT16_MAX;                      // if ability is still active or no mana
    start_turn(hero, boss);                    // start boss' turn
    if (boss.health <= 0) return mana_spent;   // if boss died from ability or poision
    boss_attack(boss, hero);
    if (hero.health <= 0) return INT16_MAX;
    return choose_ability(hero, boss, mana_spent, hard_mode);   // continue game
}

int choose_ability(Hero hero, Boss boss, int mana_spent, bool hard_mode = false) {
    return min(fight_recursive(MAGIC_MISSLE, hero, boss, mana_spent, hard_mode),
               fight_recursive(DRAIN, hero, boss, mana_spent, hard_mode),
               fight_recursive(SHIELD, hero, boss, mana_spent, hard_mode),
               fight_recursive(RECHARGE, hero, boss, mana_spent, hard_mode),
               fight_recursive(POISON, hero, boss, mana_spent, hard_mode));
}

int main() {
    auto boss_values = get_all_integers(read_entire_file("input/day_22.txt"));
    Boss boss{boss_values[0], boss_values[1]};
    Hero hero;
    print("Part 1 answer is", choose_ability(hero, boss, 0));
    print("Part 2 answer is", choose_ability(hero, boss, 0, true));
    // 2372 is too high
    // 1937
    return 0;
}