#include "simulatedannealing.h"
#include <vector>
#include <random>
#include <math.h>

template <typename T>
std::vector<T> sa(objectiveFunction<T> f, neighborghoodFunction<T> n, double a, unsigned int SAmax, double T0, std::vector<T> s)
{
    std::vector<T> sStar = s;
    std::vector<T> sLine;
    int x;
    unsigned int IterT;
    double temp = T0;
    double delta, fs, fsLine, fsStar;

    fs = f(s);
    fsStar = f(sStar);

    while (temp > 0.0001)
    {
        for (IterT = 0; IterT < SAmax; IterT++)
        {
            sLine = n(s);
            fsLine = f(sLine);
            delta = fsLine - fs;
            if (delta < 0.0)
            {
                s = sLine;
                fs = f(s);
                if (fsLine < fsStar)
                {
                    sStar = sLine;
                    fsStar = f(sStar);
                }
            }
            else
            {
                x = (double)rand() / (double)RAND_MAX;
                if (x < exp(-delta / temp))
                {
                    s = sLine;
                    fs = f(s);
                }
            }
        }
        temp = temp * a;
    }
    return sStar;
};

template std::vector<bool> sa<bool>(objectiveFunction<bool> f, neighborghoodFunction<bool> n, double a, unsigned int SAmax, double T0, std::vector<bool> s);