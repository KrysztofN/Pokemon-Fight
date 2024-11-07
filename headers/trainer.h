#include<iostream>
#include "pokemon.h"
#include<vector>

class Trainer{
    public:

    std::vector<Pokemon> pokemon;
    std::string gender;
    std::string name;
    std::string ability;
    int pokemon_count;
    int power;

    void fight();
    void add_pokemon();
    void delete_pokemon();

    Trainer() : pokemon_count(0), power(0) {}
};