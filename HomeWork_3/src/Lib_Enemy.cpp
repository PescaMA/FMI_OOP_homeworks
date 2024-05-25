#include "Utility.hpp"
#include "Lib_Enemy.hpp"
#include <iostream>

namespace LibGame{

    /*Enemy::Enemy(std::string name,int maximumHp, int maximumMana, int physicalDamage, double hitChance = 0.8,int minLvl = 1):
        Being(name,maximumHp, maximumMana, physicalDamage,hitChance),
        minLvl(minLvl){
        }*/
    Enemy::Enemy(int minLevel): minLvl(minLevel){}

    void Enemy::reset(){
        Being::reset();
        addMana(mana.getMaxVal());
    }
    void Enemy::randomizeLvl(int playerLvl){
        if(playerLvl < minLvl)
            return;
        lvl = Utility::randInt(minLvl,playerLvl);
        scaleLvl();
        hp.setVal(hp.getMaxVal());
    }
    int Enemy::getExpWorth()const{
        return getLvl();
    }
    void Enemy::setLvl(int newLvl){
        lvl = std::min(newLvl,minLvl);
        scaleLvl();
    }

    Enemy::~Enemy(){}

    Worm::Worm(void):Being("worm",10,0,3),Enemy(1){}
    void Worm::attackLogic(Being* being){
        return this->Enemy::attackLogic(being);}

    BookWorm::BookWorm(void):Being("book worm",10,3,1),Enemy(1){}
    void BookWorm::attackLogic(Being* being){
        int damage = getDamage();
        if(mana.getVal() > damage){
            std::cout << name << " drained " << damage << " mana!\n";
            being->drainMana(damage);
            drainMana(damage);
        }
        else{
            addMana(damage);
            std::cout << name << " recovered " << damage << " mana!\n";
        }
    }


    Mouse::Mouse(void):Being("mouse",20,0,5),Enemy(2){}
    void Mouse::attackLogic(Being* being){return Being::attackLogic(being);}

    Owl::Owl(void):Being("owl",30,5,6),Enemy(3){}
    void Owl::attackLogic(Being* being){
        int damage = Utility::scaleBase(2,lvl,50);
        if(mana.getVal() > damage){
            std::cout << name << " drained " << damage << " mana\n";
            being->drainMana(damage);
            drainMana(2);
            std::cout << " and lost 2 mana!\n";
        }
        else
            return Being::attackLogic(being);
    }

    InkElemental::InkElemental(void):Being("ink elemental",30,10,1),Enemy(4){}
    void InkElemental::attackLogic(Being* being){
        int damage = Utility::scaleBase(3,lvl,50);
        if(mana.getVal() > damage){
            std::cout << name << " drained " << damage << " mana\n";
            being->drainMana(damage);
            addMana(2);
            std::cout << " and gained 2 mana!\n";
        }
        Being::attackLogic(being);
    }

    LibrarianGhost::LibrarianGhost(void):Being("ghost of a librarian",40,20,0),Enemy(6){}
    void LibrarianGhost::attackLogic(Being* being){
        int damage = std::min(15,(getMana()>>1));
        if(damage > 1){
            being->takeDamage(damage);
            drainMana(damage);
            std::cout << name << " used " << damage << " mana to deal damage! ";
        }
        else{
            addMana(15);
            std::cout << name << " gained 15 mana.\n";
        }
    }

    CursedScroll::CursedScroll(void):Being("cursed scroll",40,0,15),Enemy(6){}
    void CursedScroll::attackLogic(Being* being){return Being::attackLogic(being);}

    PaperDragon::PaperDragon(void):Being("paper dragon",60,20,8),Enemy(8){}
    void PaperDragon::attackLogic(Being* being){
        int damage = std::min(10,(getMana()>>1)) + getDamage();
        if(getMana() > 5){
            being->takeDamage(damage);
            drainMana(damage);
            std::cout << name << " used " << damage << " mana to deal damage! ";
        }
        else{
            addMana(10);
            std::cout << name << " gained 15 mana.\n";
        }
    }

    ActualLibrarian::ActualLibrarian(void):Being("real librarian",100,20,8),Enemy(7){
        mana.scaleMaxVal(lvl);
        addMana(mana.getMaxVal());
    }
    void ActualLibrarian::attackLogic(Being* being){
        unsigned randomI = Utility::randInt(1,spellsLearned.size()) - 1;
        try{
            castSpell(randomI,being);
        }catch(NotEnoughMana){
            Player::attackLogic(being);
        }
    }
}
