#ifndef LIB_ENEMY_H
#define LIB_ENEMY_H

#include "Lib_Player.hpp"

namespace LibGame{

class Enemy : public Being
{
    public:
        Enemy(int,int);
        virtual ~Enemy();
        virtual int attack(Player) = 0;
    protected:

    private:
};

class Worm: public Enemy{
    public:
    Worm();
    int attack(Player player) override;
};


}
#endif // GAME_H
