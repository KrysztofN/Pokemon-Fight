#include<iostream>
#include "../headers/pokemon.h"
#include "../headers/trainer.h"
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iomanip>
#include "../headers/utils.h"

void displayWelcomeBanner() {
    std::cout << R"(
    ██████╗  ██████╗ ██╗  ██╗███████╗███╗   ███╗ ██████╗ ███╗   ██╗
    ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝████╗ ████║██╔═══██╗████╗  ██║
    ██████╔╝██║   ██║█████╔╝ █████╗  ██╔████╔██║██║   ██║██╔██╗ ██║
    ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██║╚██╔╝██║██║   ██║██║╚██╗██║
    ██║     ╚██████╔╝██║  ██╗███████╗██║ ╚═╝ ██║╚██████╔╝██║ ╚████║
    ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
    )" << '\n';
    std::cout << "=================== ADVENTURE AWAITS! ===================\n\n";
}

void slowPrint(const std::string& text, int delay = 30){
    for(char c: text){
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << std::endl;
}


int main(){
    clearScreen();
    displayWelcomeBanner();

    Trainer trainer;
    std::string input;

    slowPrint("Welcome, future Pokemon Master! What is your name?");
    std::getline(std::cin, trainer.name);

    clearScreen();
    slowPrint("Welcome, " + trainer.name + "! Choose your specialiaztion: ");
    std::cout << "\n1. Body (Acrobatics, Athletics, Combat)" << std::endl;
    std::cout << "   - Strengths: Combat, Athletics, Survival" << std::endl;
    std::cout << "   - Special: 20% boost to Pokemon's physical attacks" << std::endl;

    std::cout << "2. Mind (Education, Technology, Perception)" << std::endl;
    std::cout << "   - Strengths: Strategy, Technology, Education" << std::endl;
    std::cout << "   - Special: 15% boost to Pokemon's defense and special defense" << std::endl;

    std::cout << "3. Spirit (Charm, Command, Focus)" << std::endl;
    std::cout << "   - Strengths: Charm, Focus, Intuition" << std::endl;
    std::cout << "   - Special: 10% boost to all Pokemon's stats" << std::endl;

    int specialization;
    do{
        std::cout << "\nEnter your choice (1-3): ";
        std::cin >> specialization;
    } while (specialization < 1 || specialization > 3);
    std::cin.ignore();

    switch(specialization){
        case 1: trainer.ability_category = "Body Master"; break;
        case 2: trainer.ability_category = "Mind Master"; break;
        case 3: trainer.ability_category = "Spirit Master"; break;
    }

    clearScreen();
    slowPrint("Before starting your journey, you need to build your team!");
    slowPrint("You can have up to 5 Pokemon. Choose wisely...");

    bool startAdventure = false;
    while (!startAdventure){
        std::cout << "\nCurrent team size: " << trainer.pokemon_count << "/5\n";
        std::cout << "\n1. Add Pokemon to team";
        std::cout << "\n2. View current team";
        std::cout << "\n3. Remove Pokemon from team";
        std::cout << "\n4. Start Adventure!" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice){
            case 1:
                if(trainer.pokemon_count < 5){
                    trainer.add_pokemon();
                } else {
                    slowPrint("Your team is full! Remove a Pokemon first or start the adventure.");
                }
                break;
            case 2:
                trainer.view_pokemon();
                std::cout << "\nPress Enter to continue...";
                std::getline(std::cin, input);
                clearScreen();
                break;
            case 3:
                if(trainer.pokemon_count <= 0){
                    std::cout << "You don't have any Pokemon to delete!";
                } else{
                    trainer.delete_pokemon();
                }
                break;
            case 4:
                if(trainer.pokemon_count > 0){
                    startAdventure = true;
                } else {
                    slowPrint("You need at least one Pokemon to start your adventure!");
                }

            default:
                std::cout << "Invalid choice! Please try again" << std::endl;
        }
    }
    
    return 0;

}

