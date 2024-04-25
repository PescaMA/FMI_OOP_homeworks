#include "Lib_Enemy.hpp"
#include <iostream>

namespace LibGame{

    Enemy::Enemy(int maximumHp, int maximumMana, int physicalDamage):
        Being(maximumHp, maximumMana, physicalDamage){}
    Enemy::~Enemy(){}
    int Enemy::attack(Player player){
        player.handleAttack(dmg);
        return dmg;
    }
    Worm::Worm(void):Enemy(10,0,7){}
    int Worm::attack(Player player){return Enemy::attack(player);}
}
