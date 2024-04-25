#ifndef LIB_GAME_H
#define LIB_GAME_H
#include "Lib_Enemy.hpp"

#include <unordered_map>
#include <memory>
#include <vector>


namespace LibGame{
    class Game{
    protected:
        Player player;
        static std::vector<std::string> allEnemiesNames;
        static std::unordered_map<std::string, std::unique_ptr<Enemy> > allEnemies;

        static void loadAllEnemies();
        static Enemy* getRandomEnemy();
    public:
        Game();
        void run();
        virtual ~Game();
    };
}

#endif // Lib_Game_H
