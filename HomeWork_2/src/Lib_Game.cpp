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
void Game::makeEnemyAttack(Enemy* enemy){
    enemy->attack(&player);
}

void Game::playerAction(Enemy* enemy){
    std::cout << "\nPress 0 to pass \nPress 1 to attack:";
    int action = Utility::readInt();



    switch(action){
        case 0: {std::cout << "\nPlayer passed!\n"; break;}
        case 1: {player.attack(enemy); break;}
        default: {std::cout << "\nnot a valid command! Try again:";playerAction(enemy);}
    }
}
void Game::run(){

    Enemy* enemy = getRandomEnemy();
    playerAction(enemy);
    makeEnemyAttack(enemy);

}



Game::~Game(){
    ///Utility::cls();
    std::cout << "Game finished.\n";
}
}
