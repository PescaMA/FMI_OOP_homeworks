#include <iostream>

#include "Lib_Game.hpp"

int main(){
    LibGame::Game* test(LibGame::Game::getInstance());

    test->run();
}
