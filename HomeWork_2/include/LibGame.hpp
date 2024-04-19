#ifndef LIB_Lib_Game_H
#define LIB_Lib_Game_H

#include <memory>
#include <vector>
#include <Lib_Enemy.hpp>

class Lib_Game{
    static std::vector<std::unique_ptr<Lib_Enemy> > allEnemies;
    public:
        static void loadAllEnemies();
        Lib_Game();
        virtual ~Lib_Game();
};


#endif // Lib_Game_H
