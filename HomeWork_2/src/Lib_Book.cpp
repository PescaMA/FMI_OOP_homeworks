#include "Lib_Book.hpp"
namespace LibGame{
    Book::Book(std::string name,int baseValue, int minimumLevel = 1, double manaEfficiency = .6):
        name(name),baseVal(baseValue),minLvl(minimumLevel), manaEfficiency(manaEfficiency){}
    Book::~Book(){}
    std::ostream& operator<<(std::ostream& out, const Book& book){
        out << book.name << ' ';
        out << " Value: " << book.baseVal;
        return out;
    }

    ExpBook::ExpBook():Book("Book of experience",3,1, 1.0){}
    void ExpBook::use(Being* being) const{}
    void ExpBook::useOnSelf(Being* being) const{
        being->addExp(getBaseVal(being->getLvl()));
    }

    HealBook::HealBook():Book("Book of healing",3,3, 0.5){}
    void HealBook::use(Being* being) const{}
    void HealBook::useOnSelf(Being* being) const{
        being->addHp(getBaseVal(being->getLvl()));
    }

    HealManaBook::HealManaBook():Book("Book of mana recovery",3,3, 0.5){}
    void HealManaBook::use(Being* being) const{}
    void HealManaBook::useOnSelf(Being* being) const{
        being->addMana(getBaseVal(being->getLvl()));
    }

    FireBook::FireBook():Book("Book of fire",8,2,0.9){}
    void FireBook::use(Being* being) const{
        being->takeDamage(getBaseVal(being->getLvl()));
    }
    void FireBook::useOnSelf(Being* being) const{}


    VampirismBook::VampirismBook():Book("Book of Vampirism",4,5,.4){}
    void VampirismBook::use(Being* being) const{
        being->takeDamage(getBaseVal(being->getLvl()));
    }
    void VampirismBook::useOnSelf(Being* being) const{
        being->addHp(getBaseVal(being->getLvl()));
    }

    DrainManaBook::DrainManaBook():Book("Book of mana draining",3,1,.95){}
    void DrainManaBook::use(Being* being) const{
        being->drainMana(getBaseVal(being->getLvl()));
    }
    void DrainManaBook::useOnSelf(Being* being) const{}


    WindBook::WindBook() : Book("Book of Wind",12,3,.8){}
    void WindBook::use(Being* being) const{
        being->takeDamage(getBaseVal(being->getLvl()));
    }
    void WindBook::useOnSelf(Being* being) const{}

}
