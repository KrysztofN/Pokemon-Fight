#include<iostream>
#include "../headers/pokemon.h"
#include "../headers/trainer.h"
#include <fstream>
#include <cstdlib>


int main(){
    Trainer trainer;
    int choice;

    std::cout << "Enter trainer name: ";
    std::getline(std::cin, trainer.name);
    std::cout << "Enter trainer ability category [Body, Mind, Spirit]: ";
    std::getline(std::cin, trainer.ability_category);
    // The Body Skills are Acrobatics, Athletics, Combat, Intimidate, Stealth, and Survival.
    // The Mind Skills are General Education, Medicine Education, Occult Education, Pokémon Education, Technology Eduction, Guile, and Perception.
    // The Spirit Skills are Charm, Command, Focus, and Intuition.
    std::cout << "Enter trainer special ability: ";
    std::getline(std::cin, trainer.ability);

    //calculate trainer power
    while(true){
        std::cout << "\n1. Add pokemon\n2. Exit\nChoice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice){

            case 1:
                trainer.add_pokemon();
            case 2:
                trainer.delete_pokemon();
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
    
    return 0;

}

