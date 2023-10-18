#include "simulatedannealing.h"
#include <vector>
#include <random>
#include <math.h>

using namespace opt;

template <typename T>
SimulatedAnnealing<T>::SimulatedAnnealing(objectiveFunction<T> f, neighborhoodFunction<T> n, coolingSchedule c, double T0, double TN, unsigned long SAmax, unsigned long N)
{
    this->f = f;
    this->n = n;
    this->c = c;
    this->T0 = T0;
    this->TN = TN;
    this->SAmax = SAmax;
    this->N = N;
}
template SimulatedAnnealing<bool>::SimulatedAnnealing(objectiveFunction<bool> f, neighborhoodFunction<bool> n, coolingSchedule c, double T0, double TN, unsigned long SAmax, unsigned long N);

template <typename T>
std::vector<T> SimulatedAnnealing<T>::optimize(std::vector<T> s, std::ostream &os)
{
    std::vector<T> sStar = s;
    std::vector<T> sLine;
    double x;
    unsigned int IterT, i;
    double temp = this->T0;
    double delta, fs, fsLine, fsStar;

    fs = f(s);
    fsStar = f(sStar);

    os << fs << "," << temp << std::endl;
    for (i = 0; i < this->N; i++)
    {
        for (IterT = 0; IterT < this->SAmax; IterT++)
        {
            sLine = n(s);
            fsLine = f(sLine);
            delta = fsLine - fs;
            if (delta < 0.0)
            {
                s = sLine;
                fs = fsLine;
                if (fsLine < fsStar)
                {
                    sStar = sLine;
                    fsStar = fsLine;
                }
            }
            else
            {
                x = (double)rand() / (double)RAND_MAX;
                if (x < exp(-delta / temp))
                {
                    s = sLine;
                    fs = fsLine;
                }
            }
        }
        temp = this->c(this->T0, this->TN, this->N, i);
        os << fs << "," << temp << std::endl;
    }
    return sStar;
};
template std::vector<bool> SimulatedAnnealing<bool>::optimize(std::vector<bool> s, std::ostream &os);

double opt::coolingSchedule0(double T0, double TN, unsigned int N, unsigned int i)
{
    return T0 - (double)i * (T0 - TN) / (double)N;
}

double opt::coolingSchedule1(double T0, double TN, unsigned int N, unsigned int i)
{
    return T0 * pow(TN / T0, (double)i / (double)N);
}

double opt::coolingSchedule2(double T0, double TN, unsigned int N, unsigned int i)
{
    double a = (T0 - TN) * ((double)(N + 1)) / (double)N;
    return a / ((double)(i + 1)) + T0 - a;
}

double opt::coolingSchedule3(double T0, double TN, unsigned int N, unsigned int i)
{
    return T0 - pow(i, log(T0 - TN) / log(N));
}

double opt::coolingSchedule4(double T0, double TN, unsigned int N, unsigned int i)
{
    return TN + (T0 - TN) / (1.0 + exp(3 * ((double)i - (double)N * 0.5)));
}

double opt::coolingSchedule5(double T0, double TN, unsigned int N, unsigned int i)
{
    return 0.5 * (T0 - TN) * (1.0 + cos((double)i * M_PI / (double)N)) + TN;
}

double opt::coolingSchedule6(double T0, double TN, unsigned int N, unsigned int i)
{
    return 0.5 * (T0 - TN) * (1.0 - tanh(10.0 * (double)i / (double)N - 5.0)) + TN;
}

double opt::coolingSchedule7(double T0, double TN, unsigned int N, unsigned int i)
{
    return (T0 - TN) / cosh(10.0 * (double)i / (double)N) + TN;
}

double opt::coolingSchedule8(double T0, double TN, unsigned int N, unsigned int i)
{
    return T0 * exp(-(double)i * log(T0 / TN) / (double)N);
}

double opt::coolingSchedule9(double T0, double TN, unsigned int N, unsigned int i)
{
    return T0 * exp(-(double)(i * i) * log(T0 / TN) / (double)(N * N));
}