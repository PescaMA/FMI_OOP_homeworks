#include "Utility.hpp"
#include "Lib_Player.hpp"
#include <iostream>
namespace LibGame{

    void Player::attackLogic(Being* being){
        return Being::attackLogic(being);
    }
    Player::Player():Being("player",100,1,5){} /// default player stats.


    Player::~Player(){}
}
