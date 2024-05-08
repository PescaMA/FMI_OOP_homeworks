#include "Utility.hpp"
#include "Lib_Player.hpp"
#include <iostream>
#include <algorithm>
namespace LibGame{

    void Player::attackLogic(Being* being){
        return Being::attackLogic(being);
    }
    void Player::loadInitialBooks(){
        spellsLearned.clear();
        spellsNotLearned.clear();

        spellsLearned.emplace_back(new ExpBook);

        spellsNotLearned.emplace_back(new HealBook);
        spellsNotLearned.emplace_back(new HealManaBook);
        spellsNotLearned.emplace_back(new FireBook);
        spellsNotLearned.emplace_back(new DrainManaBook);
        spellsNotLearned.emplace_back(new VampirismBook);
        spellsNotLearned.emplace_back(new WindBook);

        std::sort(spellsNotLearned.begin(),spellsNotLearned.end(),
                  [](std::unique_ptr<Book>& ptr1,std::unique_ptr<Book>& ptr2){
                  return ptr1->getMinLvl() > ptr2->getMinLvl();});

    }

    bool Player::learnNewBook(){
        if(spellsNotLearned.empty() || spellsNotLearned.back()->getMinLvl() > lvl)
            return false;

        spellsLearned.push_back(std::move(spellsNotLearned.back()));
        spellsNotLearned.pop_back();
        return true;

    }

    Player::Player():Being("player",100,1,5){
        loadInitialBooks();
    }


    Player::~Player(){}
}
