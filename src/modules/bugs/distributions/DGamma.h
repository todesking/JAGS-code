#ifndef DGAMMA_H_
#define DGAMMA_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short gamma distribution
 * <pre>
 * X ~ dgamma(r, mu)
 * f(x|r,mu) = mu^r * x^(r - 1) * exp(-mu * x)
 * </pre>
 */
class DGamma : public RScalarDist {
 public:
  DGamma();

  double d(double x, PDFType type,
	   std::vector<double const *> const &parameters, bool give_log) const;
  double p(double q, std::vector<double const *> const &parameters, bool lower,
	   bool give_log) const;
  double q(double p, std::vector<double const *> const &parameters, bool lower,
	   bool log_p) const;
  double r(std::vector<double const *> const &parameters, RNG *rng) const;
  /**
   * Checks that r > 0, mu > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters) const;
  double KL(std::vector<double const *> const &par0,
	    std::vector<double const *> const &par1) const;
};

}}

#endif /* DGAMMA_H_ */
