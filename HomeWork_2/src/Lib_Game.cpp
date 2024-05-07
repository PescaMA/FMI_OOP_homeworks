#include "Lib_Game.hpp"
#include "Utility.hpp"
#include <iostream>
namespace LibGame{

std::unordered_map<std::string, std::unique_ptr<Enemy> > Game::allEnemies;
std::vector<std::string> Game::allEnemiesNames;

void Game::loadAllEnemies(){

    if(!allEnemies.empty())
        return; /// load only once for all games.

    allEnemies["worm"] = std::unique_ptr<Enemy>(new Worm);

    for(auto &el:allEnemies)
        allEnemiesNames.push_back(el.first);
}
Game::Game(){
    loadAllEnemies();
    std::cout << "A new journey begins.\n";
}

Enemy* Game::getRandomEnemy(){
    int i = Utility::randInt(0,allEnemies.size()-1);
    return allEnemies[allEnemiesNames[i]].get();
}
void Game::run(){
    Enemy* enemy = getRandomEnemy();

    int dmgDealt = enemy->attack(player);
    if(dmgDealt == -1){
        std::cout << "attack missed! ";
        enemy->displayHealth();
        std::cout << "\n";
    }

    else{
        std::cout << "dealt " << dmgDealt << " damage! ";
        enemy->displayHealth();
        std::cout << "\n";
    }

}



Game::~Game(){
    ///Utility::cls();
    std::cout << "Game finished.\n";
}
}
