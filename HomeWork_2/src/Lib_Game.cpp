#include "LibGame.hpp"
#include "Utility.hpp"
#include <iostream>
namespace LibGame{
std::vector<std::unique_ptr<Enemy> > Game::allEnemies;
Game::Game(){
    std::cout << "A new journey begins.\n";
}

void Game::loadAllEnemies(){
    allEnemies.clear();
    allEnemies.emplace_back(new Worm);
}

Game::~Game(){
    Utility::cls();
    std::cout << "Game finished.\n";
}
}
