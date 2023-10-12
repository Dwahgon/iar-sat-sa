#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include <functional>

template <typename T>
using objectiveFunction = std::function<double(const std::vector<T> &)>;

template <typename T>
using neighborghoodFunction = std::function<std::vector<T>(const std::vector<T> &)>;

template <typename T>
std::vector<T> sa(objectiveFunction<T> f, neighborghoodFunction<T> n, double a, unsigned int SAmax, double T0, std::vector<T> s);

#endif