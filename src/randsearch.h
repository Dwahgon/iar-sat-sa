#ifndef RAND_SEARCH_H
#define RAND_SEARCH_H

#include <vector>
#include <functional>
#include <ostream>
#include "optimizers.h"

namespace opt
{
    template <typename T>
    using randomSolutionGenerator = std::function<std::vector<T>()>;

    template <typename T>
    class RandomSearch
    {
        objectiveFunction<T> f;
        randomSolutionGenerator<T> g;
        unsigned int N;

    public:
        RandomSearch(objectiveFunction<T> f, randomSolutionGenerator<T> g, int N);
        std::vector<T> optimize(std::vector<T> s, std::ostream &os);
    };
}

#endif