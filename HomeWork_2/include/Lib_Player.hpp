#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

namespace LibGame{

class Being{
protected:
    int maxHp; /// can be changed so it shouldn't be const.
    int hp;
    int dmg; /// physical damage
    int mana = 0;

public:
    /*int getDmg() const {return dmg;}
    int getMana() const {return mana;}
    int getHP() const {return hp;}*/

    void die();
    void getAttacked(int);
    void getManaAttacked(int);
    void addHp(int);
    void addMana(int);

    Being(int,int);
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

