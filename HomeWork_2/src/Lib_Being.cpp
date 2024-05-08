#include "Lib_Being.hpp"


namespace LibGame{

    Being::Being(std::string name,int maximumHp,int maximumMana, int physicalDamage,double damageChance):
        name(name),
        hp(maximumHp),
        mana(maximumMana),
        dmg(physicalDamage),
        hitChance(damageChance){
            mana.setVal(0);
        }
    Being::Being(std::string name,int maximumHp, int maximumMana, int physicalDamage):
        Being(name,maximumHp,maximumMana,physicalDamage,0.8){}
    void Being::die(){
        std::cout << name << " died!\n";
    }
    int Being::getDamage() const {
        return dmg * lvl;
    }
    void Being::setLvl(int newLvl){
        if(newLvl <= 0)
            throw std::logic_error("Level cannot be negative!");
        lvl = newLvl;
    }
    void Being::displayHealth(std::ostream& out){
        out << name << " is at " << hp << " health.";

    }
    bool inline Being::hitAttack(){
        return Utility::randProb(hitChance);
    }
    void Being::manaDrain(int val){
        mana -= val;
    }
    void Being::takeDamage(int val){
        hp-=val;
        if(hp == 0)
            die();
    }
    void Being::addHp(int val){
        hp += val;
    }
    void Being::addMana(int val){
        mana += val;
    }
    bool Being::attack(Being* being){
        std::cout << "\n";
        if(!hitAttack()){
            std::cout << name << " missed!\n" << *being;
            return false;
        }
        attackLogic(being);
        std::cout << "\n" << *being;
        return true;
    }
    void Being::attackLogic(Being* being){
        int damage = getDamage();
        being->takeDamage(damage);
        std::cout << name << " attacked for " << getDamage() << " damage!";
    }
    std::ostream& operator<<(std::ostream& out, Being being){
        out << "( " << being.name;
        out << " level " << being.lvl;
        out << " ) HP:" <<being.hp;
        out << " ; Mana:" <<being.mana;
        out << "\n";
        return out;
    }

}
