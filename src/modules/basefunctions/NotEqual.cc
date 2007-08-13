#include <config.h>
#include "NotEqual.h"

#include <cmath>
#include <cfloat>

using std::vector;

namespace basefunctions {

NotEqual::NotEqual () : Infix ("!=")
{
}

double NotEqual::evaluateScalar(vector<double const *> const &args) const
{
  return *args[0] != *args[1];
}

bool NotEqual::isDiscreteValued(std::vector<bool> const &mask) const
{
  return true;
}

}
