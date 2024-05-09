#ifndef LIB_BOOK_H
#define LIB_BOOK_H

#include "Lib_Being.hpp"

namespace LibGame{
    class Book
    {
    protected:
        std::string name;
        int baseVal;
        int minLvl;
        int manaCost;
        void virtual use(Being*,Being*, std::ostream& out = std::cout) const = 0;
    public:
        Book(std::string,int,int,int);
        virtual ~Book();

        std::string getName()const{return name;}
        int getManaCost(){return manaCost;}
        int getMinLvl() const {return minLvl;}
        int getVal(int lvl = 1) const{
            return Utility::scale20(baseVal,lvl);
        }
        void cast(Being*, Being*, std::ostream& = std::cout);

        friend std::ostream& operator<<(std::ostream&, const Book&);
    };

    class ExpBook : public Book{
        void use(Being*,Being*,std::ostream& = std::cout) const override;

        public:
        ExpBook();
    };
    class HealBook : public Book{
        void use(Being*,Being*,std::ostream& = std::cout) const override;

        public:
        HealBook();
    };
    class HealManaBook : public Book{
        void use(Being*,Being*,std::ostream& = std::cout) const override;

        public:
        HealManaBook();
    };
    class FireBook : public Book{
        void use(Being*,Being*,std::ostream& = std::cout) const override;

        public:
        FireBook();
    };
    class DrainManaBook : public Book{
        void use(Being*,Being*,std::ostream& = std::cout) const override;

        public:
        DrainManaBook();
    };
    class VampirismBook : public Book{
        void use(Being*,Being*,std::ostream& = std::cout) const override;

        public:
        VampirismBook();
    };
    class WindBook : public Book{
        void use(Being*,Being*,std::ostream& = std::cout) const override;

        public:
        WindBook();
    };

}

#endif // GAME_H
