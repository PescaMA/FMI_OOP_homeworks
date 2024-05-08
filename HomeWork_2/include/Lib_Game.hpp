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
        std::vector<std::unique_ptr<Enemy> > fightableEnemies;
        std::vector<std::unique_ptr<Enemy> > nonFightableEnemies;

        void loadAllEnemies();
        void addNewEnemies();
        bool addNewEnemy();
        Enemy* getRandomEnemy();
        void makeEnemyAttack(Enemy*);
        void displayAttack(Being*,int);
        void playerAction(Enemy*);
    public:
        Game();
        void run();
        virtual ~Game();
    };
}

#endif // Lib_Game_H
