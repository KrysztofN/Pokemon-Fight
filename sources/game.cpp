#include <iostream>
#include "../headers/pokemon.h"
#include "../headers/trainer.h"
#include "../headers/utils.h"
#include "../headers/game.h"
#include "../headers/boss.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

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

void Trainer::train_pokemon(){
    clearScreen();
    if(pokemon_count == 0){
        std::cout << "No Pokemon to train!" << std::endl;
        return;
    }

    std::cout << "Choose a Pokemon to train: \n";
    for(int i = 0; i < pokemon_count; i++){
        std::cout << i + 1 << pokemon[i].name << std::endl;
    }

    int choice;
    std::cin >> choice;

    if(choice < 1 || choice > pokemon_count){
        std::cout << "Invalid selection!" << std::endl;
        return;
    }

    int index = choice - 1;
    Pokemon& selected_pokemon = pokemon[index];

    selected_pokemon.hp += 10;
    selected_pokemon.attack += 5;
    selected_pokemon.defense += 5;
    selected_pokemon.speed += 3;

    std::cout << selected_pokemon.name << "has completed training!\n";
    std::cout << "Stats increased!\n";
}

void Game::initialize_bosses(){
    std::vector<std::pair<std::string, std::string>> boss_configs = {
        {"Charizard" , "Dragon Tamer"},
        {"Mewtwo" , "Psychic Master"},
        {"Gyardos" , "Terror of Waters"},
        {"Drygonite" , "Hell Fire"},
        {"Gengar" , "Some Random Dude IDK"},
    };

    current_boss = 0;
    int level = 1;

    for(const auto& config : boss_configs){
        Pokemon* boss_pokemon = read_pokemon_from_database(config.first);
        if(boss_pokemon){
            bosses.emplace_back(*boss_pokemon, level, config.second, "A powerful trainer specializing in " + boss_pokemon->type1 + " type Pokemon");
        
            delete boss_pokemon;
            level++;
        }
    }
};

float Game::calculate_type_multiplier(const std::string& attacker_type, const std::string& defender_type){
    // TODO adjust the return values based on type
    if(attacker_type == "water" && defender_type == "fire") return 2.0f;
    if(attacker_type == "fire" && defender_type == "grass") return 2.0f;
    if(attacker_type == "grass" && defender_type == "water") return 2.0f;
    if(attacker_type == "electric" && defender_type == "water") return 2.0f;
    if(attacker_type == "ground" && defender_type == "electric") return 2.0f;
    if(attacker_type == "psychic" && defender_type == "fighting") return 2.0f;
    if(attacker_type == defender_type) return 0.5f;
    return 1.0f;
}

void Game::battle_turn(Pokemon& attacker, Pokemon& defender, const std::string& attacker_name){
    std::random_device rd; // seed
    std::mt19937 gen(rd()); // seed random number generator
    std::uniform_int_distribution<> damage_var(85, 100);
    std::uniform_int_distribution<> critic_chance(1, 100);

    // Calculate the damage with type effectivenes
    float type_multiplier = calculate_type_multiplier(attacker.type1, attacker.type2);

    // Critical his system (10% chance)
    bool is_critical = critic_chance(gen) <= 10;
    float critical_multiplier = is_critical ? 1.5f : 1.0f;

    int damage = static_cast<int>((attacker.attack * type_multiplier * critical_multiplier * damage_var(gen)/100.0f) - (defender.defense / 2));

    damage = std::max(1, damage); // Min 1 damage

    defender.hp -= damage;
    defender.hp = std::max(0, defender.hp); // Preventing negative hp

    std::cout << attacker_name << "'s " << attacker.name << " deals " << damage << " damage!";
    if(is_critical) std::cout << "Critical hit!";
    if(type_multiplier > 1.0f) std::cout << "It's super effective!";
    if(type_multiplier < 1.0f) std::cout << "It's not very effective...";
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Game::start_game() {
    clearScreen();
    initialize_bosses();

    std::cout << "Welcome to Pokemon Adventure, " <<trainer.name << "!\n";
    std::cout << "You must defeat " << bosses.size() << "powerful bosses to become a Pokemon Master!\n\n";

    while(current_boss < bosses.size()){
        Boss& current_boss_battle = bosses[current_boss];
        std::cout << "\n===BOSS BATTLE " << (current_boss + 1) << " ===\n";
        std::cout << "Opponent: " << current_boss_battle.name << "\n";
        std::cout << current_boss_battle.description << "\n\n";

        bool boss_defeated = battle_boss(current_boss_battle);

        if(!boss_defeated){
            std::cout << "\nGame Over! You were defeated by " << current_boss_battle.name << "!\n";
            return;
        }

        current_boss++;
        trainer.power += 100;

        if (current_boss < bosses.size()) {
            std::cout << "\nVictory! Prepare for your next challange!\n";

            // Heal the pokemon between battles ?
            for(auto& p : trainer.pokemon){
                p.hp = p.total;
            }

            // train?
            char choice;
            std::cout << "Would you like to train you Pokemon before the next battle? (y/n): ";
            std::cin >> choice;
            if(choice == 'y' || choice == 'Y'){
                trainer.train_pokemon();
            }
        }
    }

    std::cout << "Congratulation! You've defeated all bosses and become the Pokemon Champion!\n";
    std::cout << "Final Power Level: " << trainer.power << "\n";
}