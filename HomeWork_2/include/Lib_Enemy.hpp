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
    protected:
        double attackChance;

    private:
};

class Worm: public Enemy{
    public:
    Worm();
    void attackLogic(Being*) override;
};
class BookWorm: public Enemy{
    public:
    BookWorm();
    void attackLogic(Being*) override;
};
class Mouse: public Enemy{
    public:
    Mouse();
    void attackLogic(Being*) override;
};
class Owl: public Enemy{
    public:
    Owl();
    void attackLogic(Being*) override;
};
class InkElemental: public Enemy{
    public:
    InkElemental();
    void attackLogic(Being*) override;
};
class LibrarianGhost: public Enemy{
    public:
    LibrarianGhost();
    void attackLogic(Being*) override;
};
class CursedScroll: public Enemy{
    public:
    CursedScroll();
    void attackLogic(Being*) override;
};
class PaperDragon: public Enemy{
    public:
    PaperDragon();
    void attackLogic(Being*) override;
};
class ActualLibrarian: public Enemy, public Player{
    public:
    ActualLibrarian();
    void attackLogic(Being*) override;
};

}
#endif // GAME_H
