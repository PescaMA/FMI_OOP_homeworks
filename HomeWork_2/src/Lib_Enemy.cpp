#include "Lib_Enemy.hpp"
#include <iostream>

namespace LibGame{

    Enemy::Enemy(std::string name,int maximumHp, int maximumMana, int physicalDamage, double hitChance = 0.8):
        Being(name,maximumHp, maximumMana, physicalDamage,hitChance){
        std::cout << "hmm" << this->hp;
        }
    Enemy::~Enemy(){}
    int Enemy::attack(Player player){
        if(!hitAttack())
            return -1;
        player.handleAttack(dmg);
        return dmg;
    }

    Worm::Worm(void):Being("worm",10,0,3){}
    int Worm::attack(Player player){
        return this->Enemy::attack(player);}

    BookWorm::BookWorm(void):Being("book worm",10,3,1){}
    int BookWorm::attack(Player player){return Enemy::attack(player);}

    Mouse::Mouse(void):Being("mouse",20,0,5){}
    int Mouse::attack(Player player){return Enemy::attack(player);}

    Owl::Owl(void):Being("owl",40,5,6){}
    int Owl::attack(Player player){return Enemy::attack(player);}

    InkElemental::InkElemental(void):Being("ink elemental",30,10,1){}
    int InkElemental::attack(Player player){return Enemy::attack(player);}

    LibrarianGhost::LibrarianGhost(void):Being("ghost of a librarian",40,20,0){}
    int LibrarianGhost::attack(Player player){return Enemy::attack(player);}

    CursedScroll::CursedScroll(void):Being("cursed scroll",40,0,15){}
    int CursedScroll::attack(Player player){return Enemy::attack(player);}

    PaperDragon::PaperDragon(void):Being("paper dragon",60,20,8){}
    int PaperDragon::attack(Player player){return Enemy::attack(player);}

    ActualLibrarian::ActualLibrarian(void):Being("real librarian",100,40,10){}
    int ActualLibrarian::attack(Player player){return Enemy::attack(player);}
}
