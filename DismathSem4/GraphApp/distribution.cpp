#include "distribution.h"

Distribution::Distribution(const double &l, const double &m)
    : lambda(l), mu(m)
{}

double Distribution::getRandom() const{
    return mu + lambda*std::tan(2*M_PI*QRandomGenerator::global()->generateDouble());
}
