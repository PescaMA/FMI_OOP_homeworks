#include "Utility.hpp"
#include "Lib_Player.hpp"
#include <iostream>
namespace LibGame{
    Being::Being(int maximumHp, int physicalDamage):
        maxHp(maximumHp),
        hp(maximumHp),
        dmg(physicalDamage),
        mana(0){}
    void Being::die(){
        std::cout << "You died";
    }
    void Being::getAttacked(int val){
        hp -= val;
        if(hp <= 0)
            die();
    }
    void Being::getManaAttacked(int val){
        mana = std::max(0, mana - val);
    }
    void Being::addHp(int val){
        hp = std::min(hp + val, maxHp);
    }
    void Being::addMana(int val){

    }



    Player::Player():Being(100,5){}

    Player::~Player(){}
}
