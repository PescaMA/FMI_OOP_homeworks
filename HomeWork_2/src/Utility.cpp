#include "Utility.hpp"
#include <random>
namespace Utility{
    void cls(){
        system("cls||clear");
    }
    int randInt(int a, int b) {
        std::random_device rd; /// hardware entropy checker (or pseudo-random if it doesn't exist) to generate seed.
        std::mt19937 gen(rd()); /// Standard Mersenne twister engine seeded with rd().
        /// a Mersenne is a number of the form 2**n - 1. a twister means bitwise operations.

        /// Define the distribution for integers between a and b (inclusive)
        std::uniform_int_distribution<int> distribution(a, b);

        /// Generate a random number using the random engine and distribution
        return distribution(gen);
    }

}
