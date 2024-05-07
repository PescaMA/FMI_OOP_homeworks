#include "Lib_Enemy.hpp"
#include <iostream>

namespace LibGame{

    Enemy::Enemy(std::string name,int maximumHp, int maximumMana, int physicalDamage):
        Being(name,maximumHp, maximumMana, physicalDamage,0.8){}
    Enemy::~Enemy(){}
    int Enemy::attack(Player player){
        player.handleAttack(dmg);
        return dmg;
    }

    Worm::Worm(void):Enemy("?",10,0,3){}
    int Worm::attack(Player player){return Enemy::attack(player);}

    BookWorm::BookWorm(void):Enemy("?",10,3,1){}
    int BookWorm::attack(Player player){return Enemy::attack(player);}

    Mouse::Mouse(void):Enemy("?",20,0,5){}
    int Mouse::attack(Player player){return Enemy::attack(player);}

    Owl::Owl(void):Enemy("?",40,5,6){}
    int Owl::attack(Player player){return Enemy::attack(player);}

    InkElemental::InkElemental(void):Enemy("?",30,10,1){}
    int InkElemental::attack(Player player){return Enemy::attack(player);}

    LibrarianGhost::LibrarianGhost(void):Enemy("?",40,20,0){}
    int LibrarianGhost::attack(Player player){return Enemy::attack(player);}

    CursedScroll::CursedScroll(void):Enemy("?",40,0,15){}
    int CursedScroll::attack(Player player){return Enemy::attack(player);}

    PaperDragon::PaperDragon(void):Enemy("?",60,20,8){}
    int PaperDragon::attack(Player player){return Enemy::attack(player);}

    ActualLibrarian::ActualLibrarian(void):Enemy("?",100,40,10){}
    int ActualLibrarian::attack(Player player){return Enemy::attack(player);}
}
