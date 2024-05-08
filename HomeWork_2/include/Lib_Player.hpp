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
    public:
        void attackLogic (Being*) override;
        Player();
        ~Player();
    };

}
#endif // GAME_H

