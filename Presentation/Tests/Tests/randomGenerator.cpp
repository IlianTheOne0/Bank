#include "randomGenerator.h"
#include <random>

long long generateRandomLongLong(long long min, long long max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dist(min, max);

    return dist(gen);
}
