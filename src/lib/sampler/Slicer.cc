#include <config.h>
#include <sampler/Slicer.h>
#include <graph/StochasticNode.h>
#include <graph/NodeError.h>
#include <rng/RNG.h>

#include <cmath>
#include <cfloat>

//Minimum length of adaptive phase before we adjust width
#define MIN_ADAPT 10

using std::vector;

Slicer::Slicer(vector<StochasticNode *> const &nodes, Graph const &graph,
	       double width, unsigned int max)
  : Sampler(nodes, graph), _width(width), _adapt(true), _max(max),
    _sumdiff(0), _iter(0)
{
}

void Slicer::updateStep(RNG *rng)
{
  using namespace std;

  // Test current value
  double g0 = logFullConditional();
  if (isinf(g0)) {
      if (g0 > 0) {
	  return;
      }
      else {
	  throw NodeError(nodes()[0], "Current value is inconsistent with data");
      }
  }
  if (g0 == -DBL_MAX) {
    throw NodeError(nodes()[0], "Current value is inconsistent with data");
  }

  // Generate auxiliary variable
  double z = g0 - rng->exponential();;

  // Generate random interval of width "_width" about current value
  double xold = value();
  double L = xold - rng->uniform() * _width; 
  double R = L + _width;

  double lower = -DBL_MAX, upper = DBL_MAX;
  getLimits(&lower, &upper);

  // Stepping out 

  // Randomly set number of steps in left and right directions,
  // subject to the limit in the maximal size of the interval
  int j = static_cast<int>(rng->uniform() * _max);
  int k = _max - 1 - j;


  if (L < lower) {
    L = lower;
  }
  else {
    setValue(L);
    while (j-- > 0 && logFullConditional() > z) {
      L -= _width;
      if (L < lower) {
	L = lower;
	break;
      }
      setValue(L);
    }
  }

  if (R > upper) {
    R = upper;
  }
  else {
    setValue(R);
    while (k-- > 0 && logFullConditional() > z) {
      R += _width;
      if (R > upper) {
	R = upper;
	break;
      }
      setValue(R);
    }
  }

  // Keep sampling from the interval until acceptance (the loop is
  // guaranteed to terminate).
  double xnew;
  for(;;) {
    xnew =  L + rng->uniform() * (R - L);
    setValue(xnew);
    double g = logFullConditional();
    if (g >= z - DBL_EPSILON) {
      // Accept point
      break;
    }
    else {
      // shrink the interval
      if (xnew < xold) {
	L = xnew;
      }
      else {
	R = xnew;
      }
    }
  }

  if (_adapt) {
    _sumdiff += _iter * fabs(xnew - xold);
    ++_iter;
    if (_iter > MIN_ADAPT) {
      _width = 2 * _sumdiff / _iter / (_iter - 1);  
    }
  }
}

void Slicer::updateDouble(RNG *rng)
{
  using namespace std;

  // Test current value
  double g0 = logFullConditional();
  if (g0 < 0) {
    if (g0 == -DBL_MAX || isinf(g0)) {
      throw NodeError(nodes()[0], 
		      "Current value is inconsistent with data");
    }
  }
  else if (g0 == DBL_MAX || isinf(g0)) {
    return;
  }

  // Generate auxiliary variable
  double z = g0 - rng->exponential();

  // Generate random interval of width "_width" about current value
  double xold = value();
  double L = xold - rng->uniform() * _width; 
  double R = L + _width;

  double lower = -DBL_MAX, upper = DBL_MAX;
  getLimits(&lower, &upper);

  // Doubling 
  bool left_ok = false, right_ok = false;
  for (unsigned int i = 0; i < _max; ++i) {
    if (rng->uniform() < 0.5) {
      if (L >= lower) {
	L = 2*L - R;
	setValue(L);
	left_ok = logFullConditional() < z;
      }
      else {
	left_ok = true;
      }
    }
    else {
      if (R <= upper) {
	R = 2*R - L;
	setValue(R);
	right_ok = logFullConditional() < z;
      }
      else {
	right_ok = true;
      }
    }
    if (left_ok && right_ok)
      break;
  }
  
  // Keep sampling from the interval until acceptance (the loop is
  // guaranteed to terminate).
  double Lbar = L, Rbar = R;
  double xnew;
  for(;;) {
    xnew =  Lbar + rng->uniform() * (Rbar - Lbar);
    setValue(xnew);
    double g = logFullConditional();
    if (g >= z && accept(xold, xnew, z, L, R)) {
      // The accept function will alter the current value. So we must reset it.
      setValue(xnew);
      //return; No! We want to break here.
      break;
    }
    // shrink the interval
    if (xnew <= xold) {
      Lbar = xnew;
    }
    else {
      Rbar = xnew;
    }
  }

  if (_adapt) {
    _sumdiff += _iter * fabs(xnew - xold);
    ++_iter;
    if (_iter > MIN_ADAPT) {
      _width = 2 * _sumdiff / _iter / (_iter - 1);  
    }
  }
}

bool Slicer::accept(double xold, double xnew, double z, double L, double R)
{
  //Acceptance step for doubling update method

  bool d = false;
  while ((R - L) > 1.1 * _width) {
    double M = (L + R)/2;
    if ((xold < M && xnew >= M) || (xold >= M && xnew < M))
      d = true;
    if (xnew < M) {
      R = M;
    }
    else {
      L = M;
    }
    if (d) {
      setValue(R); bool right_ok = logFullConditional() < z;
      setValue(L); bool left_ok = logFullConditional() < z;
      if (left_ok && right_ok)
	return false;
    }
  }
  return true;
}  

bool Slicer::adaptOff()
{
  _adapt = false;
  return true;
}
