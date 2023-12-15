#include <iostream>
#include <random>
#include "MT.h"

// Static member initialization
std::mt19937 MT::mt_engine = std::mt19937(std::random_device{}());
std::uniform_real_distribution<double> MT::unif_dist(0.0, 1.0);
std::normal_distribution<double> MT::norm_dist(0.0, 1.0);

MT::MT() {
    // The constructor is private and does nothing in this case
}

double MT::rand_unif() {
    return unif_dist(mt_engine);
}

double MT::rand_norm() {
    return norm_dist(mt_engine);
}

std::mt19937& MT::GetMtEngine() {
    return mt_engine;
}
