#include "randsearch.h"
#include "utils.h"

using namespace opt;

template <typename T>
RandomSearch<T>::RandomSearch(objectiveFunction<T> f, randomSolutionGenerator<T> g, int N)
{
    this->f = f;
    this->g = g;
    this->N = N;
}
template RandomSearch<bool>::RandomSearch(objectiveFunction<bool> f, randomSolutionGenerator<bool> g, int N);

template <typename T>
std::vector<T> RandomSearch<T>::optimize(std::vector<T> s, std::ostream &os)
{
    std::vector<T> sOut = s, sNew;
    double sOutFo = this->f(sOut), sNewFO;
    unsigned int i;
    os << sOutFo << std::endl;
    for (i = 0; i < this->N; i++)
    {
        sNew = this->g();
        sNewFO = this->f(sNew);
        if (sNewFO < sOutFo)
        {
            sOut = sNew;
            sOutFo = sNewFO;
        }
        os << sOutFo << std::endl;
    }
    return sOut;
}
template std::vector<bool> RandomSearch<bool>::optimize(std::vector<bool> s, std::ostream &os);
