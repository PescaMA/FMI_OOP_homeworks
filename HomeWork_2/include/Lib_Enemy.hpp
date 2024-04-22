
#ifndef LIB_ENEMY_H
#define LIB_ENEMY_H

namespace LibGame{
class Enemy
{
    public:
        Enemy();
        virtual ~Enemy();
        virtual int attack() = 0;
    protected:

    private:
};

class Worm: public Enemy{
    public:
    int attack(){
        return 3;
    }
};


}
#endif // GAME_H
