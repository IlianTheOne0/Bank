#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <random>

long long generateRandomLongLong(long long min, long long max) {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<long long> distr(min, max);

    return distr(eng);
}

#endif