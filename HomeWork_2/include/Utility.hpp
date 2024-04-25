#ifndef LIB_UTILITY_H
#define LIB_UTILITY_H


#include <iostream>

namespace Utility{
    void cls(void);
    int randInt(int,int);
    bool randProb(double);

    template<class T>
    class limitedStat{

    protected:
        T val;
        T maxVal;
        void update(T newVal){
            val = std::min(newVal, maxVal);
            val = std::max(val, 0);
        }
    public:
        T getVal()const{return val;}
        void setVal(T newVal){update(newVal);}
        void setMax(T newVal){
            maxVal = newVal;
            update(val);
        }
        limitedStat(T maxVal):maxVal(maxVal){}
        void operator+(const T& addVal){
            update(val + addVal);
        }
        void operator+=(const T& addVal){val = val + addVal;}
        void operator-(const T& subVal){
            update(val - subVal);
        }
        void operator-=(const T& subVal){ val = val - subVal;}
        bool operator==(const T& val){return this->val == val;}
    };
}
#endif // Lib_UTILITY
