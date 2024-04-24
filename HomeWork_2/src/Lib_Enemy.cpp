#include "Lib_Enemy.hpp"
#include <iostream>

namespace LibGame{

    Enemy::Enemy(int maximumHp, int physicalDamage):
        Being(maximumHp, physicalDamage){}
    Enemy::~Enemy(){}
    int Enemy::attack(Player player){
        player.getAttacked(3);
        return 3;
    }
    Worm::Worm(void):Enemy(10,3){}
    Worm::attack(Player player){
        player.getAttacked(dmg);
        return dmg;
    }
}
