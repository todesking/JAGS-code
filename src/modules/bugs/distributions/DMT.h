#ifndef DMT_H_
#define DMT_H_

#include <distribution/ArrayDist.h>

namespace jags {
namespace bugs {

/**
 * @short Multivariate t distribution
 * <pre>
 * x[] ~ dmt(mu[], T[,], k)
 * </pre>
 */
class DMT: public ArrayDist {
public:
  DMT();

  double logDensity(double const *x, unsigned int length, PDFType type,
		    std::vector<double const *> const &parameters,
		    std::vector<std::vector<unsigned int> > const &dims,
		    double const *lower, double const *upper)  const;
  void randomSample(double *x, unsigned int length,
		    std::vector<double const *> const &parameters,
		    std::vector<std::vector<unsigned int> > const &dims,
		    double const *lower, double const *upper, RNG *rng) const;
  /**
   * Checks that mu is a vector, T is a square matrix and the sizes of
   * mu and T conform.
   */
  bool checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) 
      const;
  /**
   * Checks that T is symmetric and that k >= 2. Note that there is
   * currently NO CHECK that T is positive definite.
   */
  bool checkParameterValue(std::vector<double const *> const &parameters,
                           std::vector<std::vector<unsigned int> > const &dims) 
      const;
  std::vector<unsigned int> 
      dim(std::vector<std::vector<unsigned int> > const &dims) const;
  void support(double *lower, double *upper, unsigned int length,
	       std::vector<double const *> const &parameters,
               std::vector<std::vector<unsigned int> > const &dims) const;
  bool isSupportFixed(std::vector<bool> const &fixmask) const;
};

}}

#endif /* DMT_H_ */
