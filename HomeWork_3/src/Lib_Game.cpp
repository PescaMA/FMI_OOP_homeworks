#include "Lib_Game.hpp"
#include "Utility.hpp"

#include <iostream>
#include <set>
#include <algorithm>

namespace LibGame{
Game* Game::instance = NULL;
Game::Game(){
    loadAllEnemies();
    std::cout << BEGIN_MESSAGE;
}
void Game::loadAllEnemies(){

    if(!fightableEnemies.empty() || !nonFightableEnemies.empty())
        return; /// load only once for all games.

    /// upcasting :
    nonFightableEnemies.emplace_back(new Worm);
    nonFightableEnemies.emplace_back(new BookWorm);
    nonFightableEnemies.emplace_back(new Mouse);
    nonFightableEnemies.emplace_back(new Owl);
    nonFightableEnemies.emplace_back(new InkElemental);
    nonFightableEnemies.emplace_back(new CursedScroll);
    nonFightableEnemies.emplace_back(new PaperDragon);
    nonFightableEnemies.emplace_back(new ActualLibrarian);

    std::sort(nonFightableEnemies.begin(),nonFightableEnemies.end(),
                  [](std::shared_ptr<Enemy>& ptr1,std::shared_ptr<Enemy>& ptr2){
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

std::shared_ptr<Enemy> Game::getRandomEnemy(){
    if(fightableEnemies.empty())
        throw std::logic_error("no enemies are low level enough!");


    std::shared_ptr<Enemy> chosenEnemy = Utility::getRandomElement(fightableEnemies);

    chosenEnemy->randomizeLvl(player.getLvl());

    return chosenEnemy;
}
void Game::makeEnemyAttack(Enemy* enemy){
    if(enemy->isDead())
        return;
    enemy->attack(&player);
}

void Game::playerAction(Enemy* enemy){
    std::cout << "\n" << *enemy << player;
    std::cout << "Press 0 to focus (gain mana)\n";
    std::cout << "Press 1 to attack for " << player.getDamage();
    std::cout << "\nPress 2 to choose spell:";
    int action = Utility::readInt();

    Utility::cls();

    try{
    switch(action){
        case 0: {player.focus(); break;}
        case 1: {player.attack(enemy); break;}
        case 2: {player.chooseSpell(enemy);break;}
        default: {std::cout << "\nnot a valid command! Try again:";playerAction(enemy);}
    }} catch(NotEnoughMana noMana){
            std::cout << noMana.what() << "\n\nTry again:\n";
            return playerAction(enemy);
        }
}
void Game::run(){



    std::shared_ptr<Enemy> enemy = getRandomEnemy();

    std::set<std::pair<int,std::string> > defeteadEnemies;

    while(!player.isDead()){
        enemy = getRandomEnemy();
        std::cout << "Now fighting: " << *enemy;
        while(!enemy->isDead() && !player.isDead()){
            playerAction(enemy.get());
            makeEnemyAttack(enemy.get());
        }
        if(enemy->isDead()){
            player.addExp(enemy->getExpWorth());
            enemy->reset();
            defeteadEnemies.insert({enemy->getLvl(),enemy->getName()});
            addNewEnemies();

            if(dynamic_cast<ActualLibrarian*>(enemy.get()))
                break;
        }

    }
    if(player.isDead())
        std::cout << "Game over! You were defeated by " << enemy->getName() << "\n";
    else
        std::cout << "You WIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.\n";

    std::cout << "\nOn the journey you have defeated:\n";
    for(auto info : defeteadEnemies){
        std::cout << info.second << " (level " << info.first << ")\n";
    }
}

Game* Game::getInstance(){
    if(!instance)
        instance = new Game;
    return instance;
}

Game::~Game(){
    std::cout << "Game finished.\n";
}

}
