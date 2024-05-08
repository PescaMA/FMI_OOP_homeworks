#include "Lib_Game.hpp"
#include "Utility.hpp"

#include <iostream>
#include <algorithm>

namespace LibGame{

void Game::loadAllEnemies(){

    if(!fightableEnemies.empty() || !nonFightableEnemies.empty())
        return; /// load only once for all games.

    nonFightableEnemies.emplace_back(new Worm);
    nonFightableEnemies.emplace_back(new BookWorm);
    nonFightableEnemies.emplace_back(new Mouse);
    nonFightableEnemies.emplace_back(new Owl);
    nonFightableEnemies.emplace_back(new InkElemental);
    nonFightableEnemies.emplace_back(new CursedScroll);
    nonFightableEnemies.emplace_back(new PaperDragon);
    nonFightableEnemies.emplace_back(new ActualLibrarian);

    std::sort(nonFightableEnemies.begin(),nonFightableEnemies.end(),
                  [](std::unique_ptr<Enemy>& ptr1,std::unique_ptr<Enemy>& ptr2){
                  return ptr1->getMinLvl() > ptr2->getMinLvl();});

    addNewEnemies();
}
bool Game::addNewEnemy(){
    if(nonFightableEnemies.empty() || nonFightableEnemies.back()->getMinLvl() > player.getLvl())
        return false;

    fightableEnemies.push_back(std::move(nonFightableEnemies.back()));
    nonFightableEnemies.pop_back();
    return true;
}
void Game::addNewEnemies(){
    while(addNewEnemy());
}
Game::Game(){
    loadAllEnemies();
    std::cout << "A new journey begins.\n";
}

Enemy* Game::getRandomEnemy(){
    if(fightableEnemies.empty())
        throw std::logic_error("no enemies are low level enough!");
    int i = Utility::randInt(0,fightableEnemies.size()-1);
    return fightableEnemies[i].get();
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
