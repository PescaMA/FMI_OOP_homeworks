
#ifndef LIB_Lib_Enemy_H
#define LIB_Lib_Enemy_H


class Lib_Enemy
{
    public:
        Lib_Enemy();
        virtual ~Lib_Enemy();
        virtual int attack() = 0;
    protected:

    private:
};

class Worm: public Lib_Enemy{
    public:
    int attack(){
        return 3;
    }
};

#endif // GAME_H
