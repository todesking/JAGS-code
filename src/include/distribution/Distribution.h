#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_

#include <vector>
#include <string>

class SArray;
struct RNG;

/**
 * Base class for distributions.
 *
 * Distribution objects contain only constant data members and all
 * member functions are constant. Hence only one object needs to be
 * instantiated for each subclass.
 *
 * The DistTab class provides a convenient way of storing Distribution
 * objects and referencing them by name.
 * @see DistTab
 * @short Distribution of a random variable
 */
class Distribution
{
    const std::string _name;
    const unsigned int _npar;
    const bool _canbound;
    const bool _discrete;
public:
    /**
     * Constructor.
     * @param name name of the distribution as used in the BUGS language
     * @param npar number of parameters, excluding upper and lower bounds
     * @param canbound logical flag indicating whether distribution can
     * be truncated by defining lower and upper bounds.
     * @param discrete logical flag indicating whether distribution is 
     * discrete valued.
     */
    Distribution(std::string const &name, unsigned int npar, bool canbound, 
		 bool discrete);
    virtual ~Distribution();
    /**
     * @returns the BUGS language name of the distribution
     */
    std::string const &name() const;
    /**
     * @param x Value at which to evaluate the likelihood.
     *
     * @param parameters Parameter values of the distribution.  This
     * vector should be of length npar().
     *
     * @returns the log likelihood.  If the likelihood should be zero
     * because x is inconsistent with the parameters, then -DBL_MAX or
     * -Inf is returned.
     */
    virtual double 
	logLikelihood(SArray const & x, 
		      std::vector<SArray const *> const &parameters) const = 0;
    /**
     * Draws a random sample from the distribution. 
     *
     * @param x Array to which the sample values are written
     *
     * @param parameters  Vector of parameter values at which
     * to evaluate the likelihood. This vector should be of length
     * npar().
     *
     * @param r pseudo-random number generator to use.
     *
     * @exception length_error 
     */
    virtual void 
	randomSample(SArray &x,
		     std::vector<SArray const *> const &parameters,
		     RNG *r) const = 0;
    /**
     * Returns a typical value from the distribution.  The meaning of
     * this will depend on the distribution, but it will normally be a
     * mean, median or mode.
     *
     * @param x Array to which the sample values are written
     *
     * @param parameters  Vector of parameter values at which
     * to evaluate the likelihood. This vector should be of length
     * npar().
     *
     * @exception length_error 
     */
    virtual void 
	typicalValue(SArray &x, std::vector<SArray const *> const &parameters)
	const = 0;
    /**
     * The lowest possible value that X[i] can take, conditional on
     * the parameters.
     */
    /*
    virtual double 
	lowerSupport(unsigned int i,
		     std::vector<SArray const *> const &parameters) const = 0;
    */
    /**
     * The highest possible value that X[i] can take, conditional on
     * the parameters. 
     */
    /*
    virtual double 
	upperSupport(unsigned int i,
		     std::vector<SArray const *> const &parameters) const = 0;
    */
    /**
     * The number of parameters of the distribution
     */
    unsigned int npar() const;
    /**
     * Checks that dimensions of the parameters are correct.
     *
     * This function only needs to be run once for each parameter
     * vector. Thereafter, the values of the parameters will change,
     * but the dimensions will not.
     */
    virtual bool 
	checkParameterDim (std::vector<std::vector<unsigned int> > const &parameters) 
	const = 0;
    /**
     * Checks that the values of the parameters are consistent with
     * the distribution. For example, some distributions require
     * than certain parameters are positive, or lie in a given
     * range.
     *
     * This function assumes that checkParameterDim returns true.
     */
    virtual bool 
	checkParameterValue (std::vector<SArray const *> const &parameters)
	const = 0;
    /**
     * Calculates what the dimension of the distribution should be,
     * based on the distribution of its parameters.
     */
    virtual std::vector<unsigned int> 
	dim (std::vector <std::vector<unsigned int> > const &args) const = 0;
    /**
     * Returns true if the distribution has support on the integers.
     */
    bool isDiscreteValued() const;
    /**
     * Indicates whether a sampled value from the distribution is
     * determined completely by its parameters. The vast majority of
     * distributions are not deterministic, so the default method
     * returns false.
     */
    virtual bool isDeterministic() const;
    /**
     * Indicates whether a distribution is boundable using the T(,) construct
     */
    bool canBound() const;
};

#endif /* DISTRIBUTION_H_ */
