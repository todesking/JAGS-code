#ifndef DT_H_
#define DT_H_

#include "RScalarDist.h"

namespace bugs {

/**
 * t-distribution on k degrees of freedom, with median mu and
 * scale parameter tau.
 * <pre>
 * f(x|mu, tau, k)
 * f(x|0,1,k) = Gamma((k+1)/2) / (sqrt(k*pi) Gamma(k/2)) (1 + x^2/k)^-((k+1)/2)
 * </pre>
 * @short t distribution
 */
class DT : public RScalarDist {
 public:
  DT();

  double d(double x, PDFType type,
	   std::vector<double const *> const &parameters, 
	   bool log) const;
  double p(double x, std::vector<double const *> const &parameters, bool lower,
	   bool log) const;
  double q(double x, std::vector<double const *> const &parameters, bool lower,
	   bool log) const;
  double r(std::vector<double const *> const &parameters, RNG *rng) const;
  /**
   * Check that tau > 0 and k > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters) const;

};

}

#endif /* DT_H_ */
