#ifndef LIB_GAME_H
#define LIB_GAME_H
#include "Lib_Enemy.hpp"

#include <unordered_map>
#include <memory>
#include <vector>


namespace LibGame{
    class Game{ /// SINGLETON!
    private:
        Game();
        ~Game();
        static Game* instance;
    protected:
        const std::string BEGIN_MESSAGE = "A new journey begins.\n";
        Player player;
        std::vector<std::shared_ptr<Enemy> > fightableEnemies; /// polymorphism
        std::vector<std::shared_ptr<Enemy> > nonFightableEnemies; /// polymorphism

        void loadAllEnemies();
        void addNewEnemies();
        bool addNewEnemy();
        std::shared_ptr<Enemy> getRandomEnemy();
        void makeEnemyAttack(Enemy*);
        void playerAction(Enemy*);
    public:
        static Game* getInstance();
        void run();
    };
}

#endif // Lib_Game_H
