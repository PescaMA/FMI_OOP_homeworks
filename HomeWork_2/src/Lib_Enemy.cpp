#include "Lib_Enemy.hpp"
#include <iostream>

namespace LibGame{

    Enemy::Enemy(std::string name,int maximumHp, int maximumMana, int physicalDamage, double hitChance = 0.8):
        Being(name,maximumHp, maximumMana, physicalDamage,hitChance){
        std::cout << "hmm" << this->hp;
        }
    Enemy::~Enemy(){}

    Worm::Worm(void):Being("worm",10,0,3){}
    void Worm::attackLogic(Being* being){
        return this->Enemy::attackLogic(being);}

    BookWorm::BookWorm(void):Being("book worm",10,3,1){}
    void BookWorm::attackLogic(Being* being){return Being::attackLogic(being);}

    Mouse::Mouse(void):Being("mouse",20,0,5){}
    void Mouse::attackLogic(Being* being){return Being::attackLogic(being);}

    Owl::Owl(void):Being("owl",40,5,6){}
    void Owl::attackLogic(Being* being){return Being::attackLogic(being);}

    InkElemental::InkElemental(void):Being("ink elemental",30,10,1){}
    void InkElemental::attackLogic(Being* being){return Being::attackLogic(being);}

    LibrarianGhost::LibrarianGhost(void):Being("ghost of a librarian",40,20,0){}
    void LibrarianGhost::attackLogic(Being* being){return Being::attackLogic(being);}

    CursedScroll::CursedScroll(void):Being("cursed scroll",40,0,15){}
    void CursedScroll::attackLogic(Being* being){return Being::attackLogic(being);}

    PaperDragon::PaperDragon(void):Being("paper dragon",60,20,8){}
    void PaperDragon::attackLogic(Being* being){return Being::attackLogic(being);}

    ActualLibrarian::ActualLibrarian(void):Being("real librarian",100,40,10){}
    void ActualLibrarian::attackLogic(Being* being){return Being::attackLogic(being);}
}
