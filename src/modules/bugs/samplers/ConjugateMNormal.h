#ifndef CONJUGATE_M_NORMAL_H_
#define CONJUGATE_M_NORMAL_H_

#include "ConjugateMethod.h"

class Graph;

/**
 * Conjugate sampler for multivariate normal distribution
 *
 * ConjugateMNormal is currently rather limited in scope.  It can
 * sample a multivariate normal node "snode" if all the stochastic
 * children of snode in the graph are themselves multivariate normal,
 * with mean snode, and where the precision matrix does not depend on
 * snode.
 *
 * This can (and should) be extended to allow marginal stochastic
 * children that are normally distribution and where the mean of the
 * children is a linear function of (some element of) snode.
 */
class ConjugateMNormal : public ConjugateMethod {
  double *_betas;
  unsigned int _length_betas;
 public:
  ConjugateMNormal();
  ~ConjugateMNormal();
  void initialize(ConjugateSampler *sampler, Graph const &graph);
  void update(ConjugateSampler *sampler, unsigned int chain, RNG *rng) const;
  static bool canSample(StochasticNode *snode, Graph const &graph);
};

#endif /* CONJUGATE_M_NORMAL_H_ */
