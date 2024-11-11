#ifndef BOSS_H
#define BOSS_H

#include "pokemon.h"

class Boss {
public:
    Pokemon pokemon;
    int level;
    std::string name;
    std::string description;
    
    Boss(const Pokemon& p, int lvl, const std::string& n, const std::string& desc)
        : pokemon(p), level(lvl), name(n), description(desc) {
        // Scale stats based on level
        pokemon.hp *= (1 + level * 0.2);
        pokemon.attack *= (1 + level * 0.15);
        pokemon.defense *= (1 + level * 0.15);
        pokemon.speed *= (1 + level * 0.1);
    }
};

#endif