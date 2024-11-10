#include<iostream>
#include "../headers/pokemon.h"
#include "../headers/trainer.h"
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iomanip>

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayLoadingBar(const std::string& message){
    std::cout << message;
    for(int i = 0; i<20; i++){
        std::cout << " ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Done !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main(){
    clearScreen();
    Trainer trainer;
    int choice;

    std::cout << "=== Welcome to PokemonAdcenture ===";
    std::cout << "\nEnter trainer name: ";
    std::getline(std::cin, trainer.name);

    std::cout << "\nChoose trainer ability category: ";
    std::cout << "1. Body (Acrobatics, Athletics, Combat)" << std::endl;
    std::cout << "2. Mind (Education, Technology, Perception)" << std::endl;
    std::cout << "3. Spirit (Charm, Command, Focus)" << std::endl;
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
                break;
            case 2:
                trainer.delete_pokemon();
                break;
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
                break;
        }
    }
    
    return 0;

}

