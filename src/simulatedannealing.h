#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include <functional>
#include <ostream>
#include "optimizers.h"

namespace opt
{
    template <typename T>
    using neighborhoodFunction = std::function<std::vector<T>(const std::vector<T> &)>;

    using coolingSchedule = std::function<double(double T0, double TN, unsigned int N, unsigned int i)>;

    template <typename T>
    class SimulatedAnnealing
    {
        objectiveFunction<T> f;
        neighborhoodFunction<T> n;
        coolingSchedule c;
        double T0, TN;
        unsigned long SAmax, N;

    public:
        SimulatedAnnealing(objectiveFunction<T> f, neighborhoodFunction<T> n, coolingSchedule c, double T0, double TN, unsigned long SAmax, unsigned long N);
        std::vector<T> optimize(std::vector<T> s, std::ostream &os);
    };

    double coolingSchedule0(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule1(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule2(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule3(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule4(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule5(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule6(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule7(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule8(double T0, double TN, unsigned int N, unsigned int i);
    double coolingSchedule9(double T0, double TN, unsigned int N, unsigned int i);
}

#endif