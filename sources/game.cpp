#include <iostream>
#include "../headers/pokemon.h"
#include "../headers/trainer.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>

Pokemon* read_pokemon_from_database(const std::string& pokemon_name){
    std::ifstream file("../assets/pokemon.csv");
    if(!file.is_open()) {
        std::cerr << "Error: Could not open pokemon.csv" << std::endl;
        return nullptr;
    }

    std::string line;
    std::getline(file, line);

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while(std::getline(ss, cell, ',')){
            row.push_back(cell);
        }

        if (row.empty()) continue;

        std::string csv_pokemon_name = row[0];
        std::transform(csv_pokemon_name.begin(), csv_pokemon_name.end(), csv_pokemon_name.begin(), ::tolower);

        if (csv_pokemon_name == pokemon_name){
            Pokemon* new_pokemon = new Pokemon();
            new_pokemon->name = row[0];
            new_pokemon->type1 = row[1];
            new_pokemon->type2 = row[2];
            new_pokemon->total = std::stoi(row[3]);
            new_pokemon->hp = std::stoi(row[4]);
            new_pokemon->attack = std::stoi(row[5]);
            new_pokemon->defense = std::stoi(row[6]);
            new_pokemon->sp_attack = std::stoi(row[7]);
            new_pokemon->sp_defense = std::stoi(row[8]);
            new_pokemon->speed = std::stoi(row[8]);
            new_pokemon->generation = std::stoi(row[8]);
            new_pokemon->legendary = std::stoi(row[8]);

            file.close();
            return new_pokemon;
        }
    }

    file.close();
    return nullptr;
}
void Trainer::add_pokemon(){
    std::string pokemon_name;
    std::cout << "Enter pokemon name: ";
    std::getline(std::cin, pokemon_name);

    // convert to lower-case
    std::transform(pokemon_name.begin(), pokemon_name.end(), pokemon_name.begin(), ::tolower);

    Pokemon* new_pokemon = read_pokemon_from_database(pokemon_name);

    if (new_pokemon != nullptr){
        pokemon.push_back(*new_pokemon);
        pokemon_count++;
        delete new_pokemon;
    }
    
}