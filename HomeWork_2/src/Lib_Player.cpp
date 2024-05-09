#include "Utility.hpp"
#include "Lib_Player.hpp"
#include <iostream>
#include <algorithm>
namespace LibGame{

    Player::Player():Being("player",100,4,5){
        loadInitialBooks();
    }
    void Player::attackLogic(Being* being){
        return Being::attackLogic(being);
    }
    void Player::loadInitialBooks(){
        spellsLearned.clear();
        spellsNotLearned.clear();

        spellsNotLearned.emplace_back(new ExpBook);
        spellsNotLearned.emplace_back(new HealBook);
        spellsNotLearned.emplace_back(new HealManaBook);
        spellsNotLearned.emplace_back(new FireBook);
        spellsNotLearned.emplace_back(new DrainManaBook);
        spellsNotLearned.emplace_back(new VampirismBook);
        spellsNotLearned.emplace_back(new WindBook);

        std::sort(spellsNotLearned.begin(),spellsNotLearned.end(),
                  [](std::unique_ptr<Book>& ptr1,std::unique_ptr<Book>& ptr2){
                  return ptr1->getMinLvl() > ptr2->getMinLvl();});

        learnNewBooks();
    }

    bool Player::learnNewBook(){
        if(spellsNotLearned.empty() || spellsNotLearned.back()->getMinLvl() > lvl)
            return false;

        spellsLearned.push_back(std::move(spellsNotLearned.back()));
        spellsNotLearned.pop_back();
        return true;
    }
    void Player::learnNewBooks(){
        while(learnNewBook());
    }
    void Player::levelUp(){
        Being::levelUp();
        learnNewBooks();
    }
    void Player::castSpell(unsigned i,Being* target){
        if(spellsLearned.size() <= i)
            throw std::range_error("Casting non-existant spell!");
        spellsLearned[i]->cast(this,target);
    }
    void Player::chooseSpell(Being* being,std::istream& in, std::ostream& out){
        printSpells(out);
        unsigned i = static_cast<unsigned>(Utility::readInt(in,out));
        if(i == 0)
            throw std::logic_error("");
        i--;
        if(i >= spellsLearned.size()){
            Utility::cls();
            out << "Not a valid command! Try again:\n";
            return chooseSpell(being,in,out);
        }
        out << name << "Chose " << spellsLearned[i]->getName() << "!\n";

        castSpell(i,being);

    }
    void Player::printSpells(std::ostream& out){

        std::cout << "MANA: " << mana << "\n";
        std::cout << "0 to cancel\n";

        for(unsigned i = 0; i < spellsLearned.size(); ++i){
            out << i + 1 << ' ' << spellsLearned[i]->getName() << " for "<< spellsLearned[i]->getVal(lvl);
            out <<  "  ; Cost: " << spellsLearned[i]->getManaCost() << '\n';
        }
    }
    void Player::focus(){
        std::cout << getName() << " is focusing!";
        addMana(lvl);
    }

    Player::~Player(){}
}
