#ifndef POKEMON_H
#define POKEMON_H

#include <string>

class Pokemon {
public:
    std::string name;
    std::string type1;
    std::string type2;
    int total;
    int hp;
    int attack;
    int defense;
    int sp_attack;
    int sp_defense;
    int speed;
    int generation;
    bool legendary;

    void go_shiny();
    void go_evolve();
    void run_away();
};

#endif // POKEMON_H