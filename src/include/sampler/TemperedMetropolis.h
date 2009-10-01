#ifndef MIX_METHOD_H_
#define MIX_METHOD_H_

#include <sampler/Metropolis.h>
#include <vector>

class StepAdapter;

/**
 * @short Metropolis-Hastings sampling method with tempered transitions
 *
 * TemperedMetropolis implements a random-walk Metropolis-Hastings
 * method with tempered transitions (Neal, R. Sampling from multimodal
 * distributions using tempered transitions, Statistics and Computing,
 * vol 6, pp 353-355, 1996).
 *
 * A tempered log density at temperature T is derived from the target
 * log density L by replacing L with L/T.  For large T, the tempered
 * density is flattened, converging to the prior density as T tends to
 * infinity.
 *
 * In a tempered transition, a new Metropolis-Hasting proposal is
 * generated by a sequence of Metropolis-Hastings updates that are
 * stationary with respect to a tempered density.  In this sequence, T
 * starts close to 1 increases to a maximum (e.g. 1000) and then
 * decreases to 1 again. Tempering allows the proposal to jump to a
 * new local mode of the target density by tunnelling, at high
 * temperature, through a region of low density.  
 *
 * Three elements are essential for successful tempered updates. The
 * first is a sufficiently high maximum temperature. Without this,
 * tunnelling can never occur between well-separated modes of the
 * target density. The second element is a sufficiently small
 * temperature increment between levels.  If the increase is too
 * large, then the proposal generated by the tempered updates has a
 * low acceptance probability. The third element is a sufficient
 * number of replicates at each temperature level.  In
 * TemperedMetropolis the updates at each level are tuned to have an
 * acceptance probability converging to 0.234.  Several replicate
 * updates are therefore required to guarantee that a M-H jump takes
 * place. Without this, the proposal risks getting stuck in a region
 * of low probability. These elements are controlled by the parameters
 * max_level, delta, and nrep respectively.
 */
class TemperedMetropolis : public Metropolis
{
    const int _max_level;
    const double _delta; 
    const unsigned int _nrep;
    int _level;
    vector<StepAdapter*> _step_adapter;
    vector<double> _step;
    bool tempAccept(RNG *rng, double prob, int level);
    double tempUpdate(RNG *rng, int t, double pwr, double log_density0);
public:
    /**
     * Constructor.
     *
     * @param max_level Maximum number of levels 
     *
     * @param delta Increment in the log temperature at each
     * level. The maximum temperature reached is thus exp(nlevel *
     * delta).
     *
     * @param nrep Number of Metropolis-Hastings updates to do at each
     * level
     */
    TemperedMetropolis(unsigned int max_level=50, double delta = 0.10, 
		       unsigned int nrep = 4);
    ~TemperedMetropolis();
    void update(RNG *rng);
    void rescale(double prob);
    bool checkAdaptation() const;
    virtual void getValue(std::vector<double> &value) const = 0;
    virtual void setValue(std::vector<double> const &value) const = 0;
};

#endif /* MIX_METHOD_H_ */
