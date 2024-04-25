#include "Utility.hpp"
#include "Lib_Player.hpp"
#include <iostream>
namespace LibGame{

    Being::Being(int maximumHp,int maximumMana, int physicalDamage,double damageChance):
        hp(maximumHp),
        mana(maximumMana),
        dmg(physicalDamage),
        dmgChance(damageChance){
            mana.setVal(0);
        }
    Being::Being(int maximumHp, int maximumMana, int physicalDamage):
        Being(maximumHp,maximumMana,physicalDamage,0.75){}
    void Being::die(){
        std::cout << "You died";
    }
    void Being::handleAttack(int val){
        hp -= val;
        if(hp == 0)
            die();
    }
    void Being::manaDrain(int val){
        mana -= val;
    }
    void Being::addHp(int val){
        hp += val;
    }
    void Being::addMana(int val){

    }



    Player::Player():Being(100,0,5){}

    Player::~Player(){}
}
