#include "LibGame.hpp"
#include "Utility.hpp"
#include <iostream>

std::vector<std::unique_ptr<Lib_Enemy> > Lib_Game::allEnemies;
Lib_Game::Lib_Game(){
    std::cout << "A new journey begins.\n";
}

void Lib_Game::loadAllEnemies(){
    allEnemies.clear();
    allEnemies.emplace_back(new Worm);
}

Lib_Game::~Lib_Game(){
    Utility::cls();
    std::cout << "Lib_Game finished.\n";
}
