#include "Lib_Game.hpp"
#include "Utility.hpp"
#include <iostream>
namespace LibGame{

std::unordered_map<std::string, std::unique_ptr<Enemy> > Game::allEnemies;
std::vector<std::string> Game::allEnemiesNames;

Game::Game(){
    loadAllEnemies();
    std::cout << "A new journey begins.\n";
}

void Game::run(){
    int i = Utility::randInt(0,allEnemies.size()-1);
    Enemy* enemy = allEnemies[allEnemiesNames[i]].get();
    std::cout << enemy->attack(player);

}

void Game::loadAllEnemies(){

    if(!allEnemies.empty())
        return;

    allEnemies["worm"] = std::unique_ptr<Enemy>(new Worm);

    for(auto &el:allEnemies)
        allEnemiesNames.push_back(el.first);
}

Game::~Game(){
    ///Utility::cls();
    std::cout << "Game finished.\n";
}
}
