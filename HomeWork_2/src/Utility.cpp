#include "Utility.hpp"
#include <random>
#include <cstdlib>
#include <iostream>
#include <chrono>
namespace Utility{

    int readInt(std::istream& in,std::ostream& out){
        try{
            std::string s;
            in >> s;
            return stoi(s);
        }
        catch (std::invalid_argument){
            out << "input a integer! Try again:";
            return readInt(in,out);
        }
    }
    void cls(){
        system("cls||clear");
    }
    int randInt(int a, int b) {
        static unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        static std::mt19937 gen(seed); /// Standard Mersenne twister engine.
        /// a Mersenne is a number of the form 2**n - 1. a twister means bitwise operations.

        /// Define the distribution for integers between a and b (inclusive)
        std::uniform_int_distribution<int> distribution(a, b);

        /// Generate a random number using the random engine and distribution
        return distribution(gen);
    }
    bool randProb(double probability){
        if(probability < 0 || probability > 1)
            throw std::invalid_argument("not a valid probability percentage! ");

        static unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        static std::mt19937 gen(seed);
        static std::uniform_real_distribution<double> dist(0.0, 1.0);

        double random_value = dist(gen);

        /// Check if the random value is less than the specified probability
        return random_value <= probability;
    }

}
