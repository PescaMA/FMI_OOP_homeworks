#ifndef LIB_BOOK_H
#define LIB_BOOK_H

#include "Lib_Being.hpp"

namespace LibGame{
    class Book
    {
        std::string name;
        int baseVal;
        int minLvl;
        double manaEfficiency;
        public:
            Book(std::string,int,int,double);
            virtual ~Book();

            std::string getName()const{return name;}
            int getManaCost(){
                return manaEfficiency * baseVal;
            }
            int getMinLvl() const {return minLvl;}
            int getBaseVal(int lvl = 1) const{
                int modifier = static_cast<int>(lvl) * .4;
                return baseVal * std::min(modifier, 1);
            }

            void virtual use(Being*) const = 0;
            void virtual useOnSelf(Being*) const = 0;
            friend std::ostream& operator<<(std::ostream&, const Book&);
    };

    class ExpBook : public Book{
        public:
        ExpBook();
        void use(Being* being) const override;
        void useOnSelf(Being* being) const override;
    };
    class HealBook : public Book{
        public:
        HealBook();
        void use(Being* being) const override;
        void useOnSelf(Being* being) const override;
    };
    class HealManaBook : public Book{
        public:
        HealManaBook();
        void use(Being* being) const override;
        void useOnSelf(Being* being) const override;
    };
    class FireBook : public Book{
        public:
        FireBook();
        void use(Being* being) const override;
        void useOnSelf(Being* being) const override;
    };
    class DrainManaBook : public Book{
        public:
        DrainManaBook();
        void use(Being* being) const override;
        void useOnSelf(Being* being) const override;
    };
    class VampirismBook : public Book{
        public:
        VampirismBook();
        void use(Being* being) const override;
        void useOnSelf(Being* being) const override;
    };
    class WindBook : public Book{
        public:
        WindBook();
        void use(Being* being) const override;
        void useOnSelf(Being* being) const override;
    };

}

#endif // GAME_H
