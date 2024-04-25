#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H
#include "Utility.hpp"

#include <string>

namespace LibGame{



class Being{
protected:
    Utility::limitedStat<int> hp;
    Utility::limitedStat<int> mana;

    int dmg; /// physical damage
    double dmgChance = .75;
    std::string name;

public:
    /*int getDmg() const {return dmg;}
    int getMana() const {return mana;}
    int getHP() const {return hp;}*/

    void die();
    void handleAttack(int);
    void manaDrain(int);
    void addHp(int);
    void addMana(int);

    Being(int,int,int);
    Being(int,int,int,double);
    ~Being(){}
};


class Player : public Being{
public:
    void attack();
    Player();
    ~Player();
};

}
#endif // GAME_H

