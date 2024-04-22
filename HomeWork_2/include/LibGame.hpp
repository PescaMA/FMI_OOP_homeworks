#ifndef LIB_GAME_H
#define LIB_GAME_H
#include <memory>
#include <vector>
#include "Lib_Enemy.hpp"

namespace LibGame{
    class Game{
        static std::vector<std::unique_ptr<Enemy> > allEnemies;
        public:
            static void loadAllEnemies();
            Game();
            virtual ~Game();
    };
}

#endif // Lib_Game_H
