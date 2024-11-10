#include <iostream>
#include "../headers/pokemon.h"
#include "../headers/trainer.h"
#include "../utils/utils.cpp"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>

Pokemon* read_pokemon_from_database(const std::string& pokemon_name){
    std::ifstream file("./assets/pokemon.csv");
    if(!file.is_open()) {
        std::cerr << "Error: Could not open pokemon.csv" << std::endl;
        return nullptr;
    }

    std::string line;
    std::getline(file, line);

    std::cout << "Header line: " << line << std::endl;

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while(std::getline(ss, cell, ',')){
            row.push_back(cell);
        }

        if (row.empty()) continue;

        std::string csv_pokemon_name = row[1];
        std::cout << "Checking pokemon: '" << csv_pokemon_name << "'" << std::endl;
        std::transform(csv_pokemon_name.begin(), csv_pokemon_name.end(), csv_pokemon_name.begin(), ::tolower);

        if (csv_pokemon_name == pokemon_name){
            std::cout << "Found matching pokemon!" << std::endl;
            Pokemon* new_pokemon = new Pokemon();
            new_pokemon->name = row[1];
            new_pokemon->type1 = row[2];
            new_pokemon->type2 = row[3];
            new_pokemon->total = std::stoi(row[4]);
            new_pokemon->hp = std::stoi(row[5]);
            new_pokemon->attack = std::stoi(row[6]);
            new_pokemon->defense = std::stoi(row[7]);
            new_pokemon->sp_attack = std::stoi(row[8]);
            new_pokemon->sp_defense = std::stoi(row[9]);
            new_pokemon->speed = std::stoi(row[10]);
            new_pokemon->generation = std::stoi(row[11]);
            new_pokemon->legendary = (row[12] == "True" || row[12] == "1"); 

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

    std::transform(pokemon_name.begin(), pokemon_name.end(), pokemon_name.begin(), ::tolower);

    Pokemon* new_pokemon = read_pokemon_from_database(pokemon_name);

    if (new_pokemon != nullptr){
        pokemon.push_back(*new_pokemon);
        pokemon_count++;
        delete new_pokemon;
        std::cout<< "Hurray! You added " << pokemon_name << "to your team!" << std::endl;
    }
    else{
        std::cout << "Pokemon not found! Or it has mightfuly tricked you not to see it..." << std::endl;
    }
}

void Trainer::delete_pokemon(){
    if(pokemon_count == 0){
        std::cout << "No Pokemon to delete! "<< std::endl;
        return;
    }

    std::cout << "Current Deck: " << std::endl;
    for(int i=0; i < pokemon_count; i++){
        std::cout << i+1 << ". " << pokemon[i].name << std::endl;
    }

    int choice;
    std::cout << "Enter the number of the Pokemon to delete (1 - " << pokemon_count << "): ";
    std::cin >> choice;

    if(choice < 1 || choice > pokemon_count){
        std::cout << "Invalid selection!" << std::endl;
        return;
    }

    int index = choice - 1;

    std::string deleted_name = pokemon[index].name;

    pokemon.erase(pokemon.begin() + index);
    pokemon_count--;

    std::cout << deleted_name << " has been removed from your team!" << std::endl;

}

void Trainer::view_pokemon(){
    clearScreen();
    if(pokemon_count == 0){
        std::cout << "You don't have any pokemon yet!" << std::endl;
        return;
    }

    std::cout << "\n=== Your Pokemon Team ===" << std::endl;
    for(int i = 0; i < pokemon_count; i++){
        std::cout << "\nPokemon #" << i + 1 << std::endl;
        std::cout << "Name: " << pokemon[i].name << std::endl;
        std::cout << "Type: " << pokemon[i].type1;
        if (!pokemon[i].type2.empty()) std::cout << "/" << pokemon[i].type2;
        std::cout << "\nHP: " << pokemon[i].hp << std::endl;
        std::cout << "Attack: " << pokemon[i].attack << std::endl;
        std::cout << "Defense: " << pokemon[i].defense << std::endl;
        std::cout << "Speed: " << pokemon[i].speed << std::endl;
        std::cout << "------------------------" << std::endl;
    }

}