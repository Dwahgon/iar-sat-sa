#ifndef OPTIMIZERS_H
#define OPTIMIZERS_H

namespace opt
{
    template <typename T>
    using objectiveFunction = std::function<double(const std::vector<T> &)>;
}

#endif