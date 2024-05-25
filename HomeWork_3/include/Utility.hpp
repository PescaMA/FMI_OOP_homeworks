#ifndef LIB_UTILITY_H
#define LIB_UTILITY_H

#include <iostream>
#include <vector>

namespace Utility{
    int readInt(std::istream& = std::cin,std::ostream& out = std::cout);
    void cls(void);
    int randInt(int,int);
    bool randProb(double);
    int scaleBase(int,int,int);
    int scale20(int,int);

    template<class T>
    class limitedStat{

    protected:
        T maxVal;
        const T baseMaxVal;
        T val;
        void update(T newVal){
            val = std::min(newVal, maxVal);
            val = std::max(val, 0);
        }
    public:
        limitedStat(T maxVal):maxVal(maxVal),baseMaxVal(maxVal),val(maxVal){}
        T getVal()const{return val;}
        T getMaxVal() const {return maxVal;}
        void scaleMaxVal(int value,int scale = 20){maxVal = scaleBase(baseMaxVal,value,scale);
        update(val);}
        void setVal(T newVal){update(newVal);}
        void setMax(T newVal){
            maxVal = newVal;
            update(val);
        }
        void operator+(const T& addVal){
            update(val + addVal);
        }
        void operator+=(const T& addVal){*this + addVal;}

        void operator-(const T& subVal){
            update(val - subVal);
        }
        void operator-=(const T& subVal){*this - subVal;}

        bool operator==(const T& val){return this->val == val;}
        friend std::ostream& operator<<(std::ostream& out, const limitedStat& stat){
            out << stat.val << "/" << stat.getMaxVal();
            return out;
        }
    };
}
#endif // Lib_UTILITY
