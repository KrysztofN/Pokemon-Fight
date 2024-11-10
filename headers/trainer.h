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

    Trainer() : pokemon_count(0), power(0) {}
};

#endif // TRAINER_H