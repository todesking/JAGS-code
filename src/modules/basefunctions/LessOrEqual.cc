#include <config.h>
#include "LessOrEqual.h"

#include <cmath>
#include <cfloat>

using std::vector;

namespace basefunctions {

LessOrEqual::LessOrEqual () : Infix ("<=")
{
}

double LessOrEqual::evaluateScalar(vector<double const *> const &args) const
{
  return *args[0] <= *args[1];
}

bool LessOrEqual::isDiscreteValued(std::vector<bool> const &mask) const
{
  return true;
}

}
