#include "utils.h"
#include <vector>
#include <random>

std::vector<bool> randomBoolVector(std::size_t size)
{
    std::vector<bool> v;
    while (size--)
    {
        v.push_back((bool)(rand() % 2));
    }
    return v;
}