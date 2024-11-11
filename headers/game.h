#ifndef GAME_H
#define GAME_H

#include<iostream>
#include "trainer.h"
#include "pokemon.h"
#include "boss.h"

class Game{
    private:
        Trainer& trainer;
        std::vector<Boss> bosses;
        int current_boss;

        void  initialize_bosses(){};
        float calculate_type_multiplier(const std::string& attacker_type, const std::string& defender_type){};
        void  battle_turn(Pokemon& attacker, Pokemon& defender, const std::string& attacker_name){};
    
    public:
        Game(Trainer& t) : trainer(t) {};
        void start_game();
        bool battle_boss(Boss& boss);
};


#endif // GAME_H