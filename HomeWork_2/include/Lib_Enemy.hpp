#ifndef LIB_ENEMY_H
#define LIB_ENEMY_H

#include "Lib_Player.hpp"

namespace LibGame{

class Enemy :virtual public Being
{
    public:
        Enemy(){}
        Enemy(std::string,int,int,int,double);
        virtual ~Enemy();
        virtual int attack(Player) = 0;
    protected:
        double attackChance;

    private:
};

class Worm: public Enemy{
    public:
    Worm();
    int attack(Player player) override;
};
class BookWorm: public Enemy{
    public:
    BookWorm();
    int attack(Player player) override;
};
class Mouse: public Enemy{
    public:
    Mouse();
    int attack(Player player) override;
};
class Owl: public Enemy{
    public:
    Owl();
    int attack(Player player) override;
};
class InkElemental: public Enemy{
    public:
    InkElemental();
    int attack(Player player) override;
};
class LibrarianGhost: public Enemy{
    public:
    LibrarianGhost();
    int attack(Player player) override;
};
class CursedScroll: public Enemy{
    public:
    CursedScroll();
    int attack(Player player) override;
};
class PaperDragon: public Enemy{
    public:
    PaperDragon();
    int attack(Player player) override;
};
class ActualLibrarian: public Enemy, public Player{
    public:
    ActualLibrarian();
    int attack(Player player) override;
};

}
#endif // GAME_H
