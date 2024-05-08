#include "Lib_Being.hpp"


namespace LibGame{

    void Hp::takeDamage(int val){
        hp-=val;
        if(hp == 0)
            die();
    }
    void Exp::setLvl(int newLvl){
        if(newLvl <= 0)
            throw std::logic_error("Level cannot be negative!");
        lvl = newLvl;
    }
    int Exp::getLevelUpExp(){
        return ( 1 << lvl );
    }
    void Exp::levelUp(){
        xp = 0;
        lvl++;
    }
    void Exp::addExp(int val){
        if(val < 0)
            throw std::runtime_error("Experience points can't be negative!");
        while(xp + val >= getLevelUpExp()){
            val -= getLevelUpExp() - xp;
            levelUp();
        }
        xp += val;
    }

    Being::Being(std::string name,int maximumHp,int maximumMana, int physicalDamage,double damageChance):
        Hp(maximumHp),
        Mana(maximumMana),
        name(name),
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

    bool inline Being::hitAttack(){
        return Utility::randProb(hitChance);
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
