#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

#include <vector>
#include <memory>

#include "Utility.hpp"
#include "Lib_Being.hpp"
#include "Lib_Book.hpp"



namespace LibGame{

    class Player : virtual public Being{
        std::vector<std::unique_ptr<Book>> spellsLearned;
        std::vector<std::unique_ptr<Book>> spellsNotLearned;
        void loadInitialBooks();
        bool learnNewBook();
        void learnNewBooks();
    public:
        void levelUp() override;
        void attackLogic (Being*) override;
        void chooseSpell(Being*,std::istream& in = std::cin, std::ostream& = std::cout);
        void printSpells(std::ostream& = std::cout);
        void castSpell(unsigned,Being*);
        Player();
        ~Player();
    };

}
#endif // GAME_H

