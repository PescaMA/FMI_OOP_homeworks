#ifndef LIB_BEING_H
#define LIB_BEING_H

#include "Utility.hpp"

namespace LibGame{
    class attackMiss : public std::exception {
        public:
        const char * what () {
            return "Attack missed. ";
        }
    };
    class Being{
    protected:
        std::string name = "?";
        Utility::limitedStat<int> hp;
        Utility::limitedStat<int> mana;
        int dmg; /// physical damage
        double hitChance = .8;
        int lvl = 1;

        void die();
    public:
        int getDamage() const;
        /*
        int getMana() const {return mana;}
        int getHP() const {return hp;}*/
        double getHitChance(){return hitChance;}
        int getLvl(){return lvl;}
        void setLvl(int);

        bool hitAttack();
        bool attack(Being*);
        virtual void attackLogic(Being*);
        void handleAttack(Being*);
        void manaDrain(int);
        void takeDamage(int);
        void addHp(int);
        void addMana(int);
        void displayHealth(std::ostream& = std::cout);

        Being(void):hp(0),mana(0){}
        Being(std::string,int,int,int);
        Being(std::string,int,int,int,double);
        virtual ~Being(){}
        friend std::ostream& operator<<(std::ostream&, Being);
    };
}

#endif // LIB_BEING.H
