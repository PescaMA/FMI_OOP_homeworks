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
    void Exp::printExp(std::ostream& out){
        out << xp << "/" << getLevelUpExp();
    }

    void Being::scaleLvl(){
        hp.scaleMaxVal(lvl,10);
        mana.scaleMaxVal(lvl,50);
    }
    void Being::levelUp(){
        std:: cout << "\n" <<  getName() << " leveled up!\n";
        Exp::levelUp();
        scaleLvl();
    }
    void Being::addExp(int val){
        std:: cout << "\n" <<  getName() << " gained " << val << " exp!\n";
        Exp::addExp(val);

    }
    Being::Being(std::string name,int maximumHp,int maximumMana, int physicalDamage,double damageChance):
        Hp(maximumHp),
        Mana(maximumMana),
        name(name),
        dmg(physicalDamage),
        hitChance(damageChance){
            mana.setVal(0);
            scaleLvl();
        }
    Being::Being(std::string name,int maximumHp, int maximumMana, int physicalDamage):
        Being(name,maximumHp,maximumMana,physicalDamage,0.8){}

    void Being::reset(){
        hp.setVal(hp.getMaxVal());
        mana.setVal(0);
    }
    void Being::die(){
        std::cout << name << " died!\n\n\n";
    }
    int Being::getDamage() const {
        return Utility::scale20(dmg,lvl);
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
        return true;
    }
    void Being::attackLogic(Being* being){
        int damage = getDamage();
        std::cout << name << " attacked for " << damage << " damage!\n";
        being->takeDamage(damage);

    }
    std::ostream& operator<<(std::ostream& out, Being being){
        out << "( " << being.name;
        out << " level " << being.lvl;
        out << " ) HP:" <<being.hp;
        out << " ; Mana:" <<being.mana;
        out << " ; XP: "; being.printExp();
        out << " ; Dmg: " << being.getDamage();
        out << "\n";
        return out;
    }

}
