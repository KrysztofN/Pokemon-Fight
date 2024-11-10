#ifndef TRAINER_H
#define TRAINER_H

#include<iostream>
#include "pokemon.h"
#include<vector>

class Trainer{
    public:

    std::vector<Pokemon> pokemon;
    std::string name;
    std::string ability_category;
    std::string ability;
    int pokemon_count;
    int power;

    void fight();
    void add_pokemon();
    void delete_pokemon();
    void view_pokemon();

    Trainer() : pokemon_count(0), power(0) {}

    private:
        int money = 1000;
        int badges = 0;
        std::string rank = "Novice";
};

#endif // TRAINER_H