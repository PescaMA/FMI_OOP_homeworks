#ifndef LIB_BEING_H
#define LIB_BEING_H

#include "Utility.hpp"

namespace LibGame{


    class Hp{
    protected:
        Utility::limitedStat<int> hp;
        virtual void die() = 0; /// pure virtual.
    public:
        Hp(int val = 0):hp(val){}
        int getHP() const {return hp.getVal();}
        void addHp(int val){hp += val;}
        bool isDead(){return hp == 0;}
        void takeDamage(int);
    };

    class Mana{
    protected:
        Utility::limitedStat<int> mana;
    public:
        Mana(int val = 0):mana(val){}
        int getMana() const {return mana.getVal();}
        void addMana(int val){mana += val;}
        void drainMana(int val){mana -= val;}
    };

    class Exp{
    protected:
        int lvl = 1;
        int xp = 0;
        void printExp(std::ostream& out = std::cout);
    public:
        int getExp()const{return xp;}
        virtual void levelUp();
        int getLevelUpExp();
        int getLvl()const{return lvl;}
        virtual void setLvl(int);
        virtual void addExp(int);
    };
    class Being : public Hp, public Mana, public Exp{
    protected:
        std::string name = "?";
        int dmg; /// physical damage
        double hitChance = .8;

        void die() override;
    public:
        virtual void reset();
        int getDamage() const;
        void scaleLvl();

        const std::string& getName() const{return name;}
        double getHitChance(){return hitChance;}
        bool hitAttack();
        bool attack(Being*);
        virtual void attackLogic(Being*);
        virtual void levelUp() override;
        virtual void addExp(int) override;

        Being(void):Hp(0),Mana(0){}
        Being(std::string,int,int,int);
        Being(std::string,int,int,int,double);
        virtual ~Being(){}
        friend std::ostream& operator<<(std::ostream&, Being);
    };
}

#endif // LIB_BEING.H
