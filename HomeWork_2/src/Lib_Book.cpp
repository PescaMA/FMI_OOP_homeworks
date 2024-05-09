#include "Lib_Book.hpp"
namespace LibGame{
    Book::Book(std::string name,int baseValue, int minimumLevel = 1, int manaCost = 100):
        name(name),baseVal(baseValue),minLvl(minimumLevel), manaCost(manaCost){}
    Book::~Book(){}
    void Book::cast(Being *caster, Being* target, std::ostream& out){
            if(caster->getMana() < getManaCost())
                throw std::logic_error("Not enough mana!");
            caster->drainMana(getManaCost());
            use(caster,target,out);
        }
    std::ostream& operator<<(std::ostream& out, const Book& book){
        out << book.name << ' ';
        out << " Value: " << book.baseVal;
        return out;
    }

    ExpBook::ExpBook():Book("Book of experience",3,1, 2){}
    void ExpBook::use(Being* caster,Being* target, std::ostream& out)const{
        ///out << caster->getName() << " gained " << getVal(caster->getLvl()) << " Exp! \n";
        caster->addExp(getVal(caster->getLvl()));
    }

    DrainManaBook::DrainManaBook():Book("Book of mana draining",3,1,1){}
    void DrainManaBook::use(Being* caster,Being* target, std::ostream& out) const{
        int manaDamage = getVal(caster->getLvl());
        out << caster->getName() << " drained " << manaDamage  << " mana from " << target->getName() << "\n";
        int enemyMana = target->getMana();
        target->drainMana(manaDamage);
        caster->addMana(std::min(enemyMana,manaDamage));
    }

    FireBook::FireBook():Book("Book of fire",8,2,3){}
    void FireBook::use(Being* caster,Being* target, std::ostream& out) const{
        out << caster->getName() << " dealt " << getVal(caster->getLvl()) << " fire damage to " << target->getName() << "\n";
        target->takeDamage(getVal(caster->getLvl()));
    }

    HealBook::HealBook():Book("Book of healing",12,3, 4){}
    void HealBook::use(Being* caster,Being* target, std::ostream& out) const{
        out << caster->getName() << " healed " << getVal(caster->getLvl()) << " hp! \n";
        caster->addHp(getVal(caster->getLvl()));
    }

    HealManaBook::HealManaBook():Book("Book of mana recovery",5,3,3){}
    void HealManaBook::use(Being* caster,Being* target, std::ostream& out) const{
        out << caster->getName() << " gained " << getVal(caster->getLvl()) << " mana! \n";
        caster->addMana(getVal(caster->getLvl()));
    }

    VampirismBook::VampirismBook():Book("Book of Vampirism",10,5,7){}
    void VampirismBook::use(Being* caster,Being* target, std::ostream& out) const{
        out << caster->getName() << " stole " << getVal(caster->getLvl()) << " hp from " << target->getName() << "\n";
        target->takeDamage(getVal(caster->getLvl()));
        caster->addHp(getVal(caster->getLvl()));
    }


    WindBook::WindBook() : Book("Book of Wind",16,3,6){}
    void WindBook::use(Being* caster,Being* target, std::ostream& out) const{
        out << caster->getName() << " dealt " << getVal(caster->getLvl()) << " wind damage to " << target->getName() << "\n";
        target->takeDamage(getVal(caster->getLvl()));
    }

}
