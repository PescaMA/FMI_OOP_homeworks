#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H
#include "Utility.hpp"
#include "Lib_Being.hpp"

#include <string>

namespace LibGame{

    class Player : virtual public Being{
    public:
        void attackLogic (Being*) override;
        Player();
        ~Player();
    };

}
#endif // GAME_H

