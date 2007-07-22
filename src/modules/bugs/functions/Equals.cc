#include <config.h>
#include "Equals.h"

#include <cmath>
#include <cfloat>

using std::vector;
using std::fabs;

Equals::Equals () : ScalarFunc ("equals",2)
{
}

double Equals::eval (vector<double const *> const &args) const
{
  return fabs(*args[0] - *args[1]) < 16 *DBL_EPSILON;
}

bool Equals::isDiscreteValued(std::vector<bool> const &mask) const
{
  return true;
}
