#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H
#include "Utility.hpp"

#include <string>

namespace LibGame{

class Being{
protected:
    std::string name = "?";
    Utility::limitedStat<int> hp;
    Utility::limitedStat<int> mana;
    int dmg; /// physical damage
    double hitChance = .8;

    void die();
public:
    /*int getDmg() const {return dmg;}
    int getMana() const {return mana;}
    int getHP() const {return hp;}*/
    double getHitChance(){return hitChance;}

    void handleAttack(int);
    void manaDrain(int);
    void addHp(int);
    void addMana(int);

    Being(void):hp(0),mana(0){}
    Being(std::string,int,int,int);
    Being(std::string,int,int,int,double);
    virtual ~Being(){}
};


class Player : virtual public Being{
public:
    void attack();
    Player();
    ~Player();
};

}
#endif // GAME_H

