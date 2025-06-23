#include "Util.h"
#include <random>
#include <chrono>

namespace RandomUitl
{
    std::mt19937& GetEngine()
    {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }

    int GetRandomInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(GetEngine());
    }
}

