#include <iostream>
#include <random>

class MT {
private:
    static std::mt19937 mt_engine;
    static std::uniform_real_distribution<double> unif_dist;
    static std::normal_distribution<double> norm_dist;

    MT(); // Private constructor
public:
    // Delete copy constructor and assignment operator
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    // Get a uniform random number
    static double rand_unif();

    // Get a normal random number
    static double rand_norm();

    // Getter for mt_engine
    static std::mt19937& GetMtEngine();
};