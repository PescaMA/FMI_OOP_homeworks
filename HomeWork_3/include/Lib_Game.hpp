#ifndef LIB_GAME_H
#define LIB_GAME_H
#include "Lib_Enemy.hpp"

#include <unordered_map>
#include <memory>
#include <vector>


namespace LibGame{
    class Game{
    protected:
        const std::string BEGIN_MESSAGE = "A new journey begins.\n";
        static Player player;
        static std::vector<std::unique_ptr<Enemy> > fightableEnemies; /// polymorphism
        static std::vector<std::unique_ptr<Enemy> > nonFightableEnemies; /// polymorphism

        static void loadAllEnemies();
        static void addNewEnemies();
        static bool addNewEnemy();
        static Enemy* getRandomEnemy();
        static void makeEnemyAttack(Enemy*);
        static void playerAction(Enemy*);
    public:
        Game();
        static void run();
        virtual ~Game();
    };
}

#endif // Lib_Game_H
