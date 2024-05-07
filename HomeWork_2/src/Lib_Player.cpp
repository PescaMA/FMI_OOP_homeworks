#include "Utility.hpp"
#include "Lib_Player.hpp"
#include <iostream>
namespace LibGame{

    Being::Being(std::string name,int maximumHp,int maximumMana, int physicalDamage,double damageChance):
        name(name),
        hp(maximumHp),
        mana(maximumMana),
        dmg(physicalDamage),
        hitChance(damageChance){
            mana.setVal(0);
        }
    Being::Being(std::string name,int maximumHp, int maximumMana, int physicalDamage):
        Being(name,maximumHp,maximumMana,physicalDamage,0.75){}
    void Being::die(){
        std::cout << name << " died!\n";
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
        mana += val;
    }



    Player::Player():Being("player",100,1,5){} /// default player stats.

    Player::~Player(){}
}
