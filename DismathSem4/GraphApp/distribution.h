#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QRandomGenerator>
#include <cmath>

class Distribution
{
    double lambda;
    double mu;
public:
    Distribution(const double& l, const double& m);

    double getRandom() const;
};

#endif // DISTRIBUTION_H
