#include <config.h>
#include <distribution/ArrayDist.h>
#include <util/dim.h>
#include <util/nainf.h>

using std::string;
using std::vector;

namespace jags {

ArrayDist::ArrayDist(string const &name, unsigned int npar)
  : Distribution(name, npar)
{
}

unsigned long ArrayDist::df(vector<vector<unsigned long> > const &pdims) const
{
    return product(dim(pdims));
}

    
    double ArrayDist::KL(vector<double const *> const &par1,
			 vector<double const *> const &par2,
			 vector<vector<unsigned long> > const &dims,
			 double const *lower, double const *upper,
			 RNG *rng, unsigned int nrep) const
    {
	double div = 0;

	vector<unsigned long> d = dim(dims);
	unsigned long N = product(d);
	vector<double> v(N);
	for (unsigned int r = 0; r < nrep; ++r) {
	    randomSample(&v[0], N, par1, dims, lower, upper, rng);
	    div += logDensity(&v[0], N, PDF_FULL, par1, dims, lower, upper);
	    div -= logDensity(&v[0], N, PDF_FULL, par2, dims, lower, upper);
	}
	return div / nrep;
    }

    double ArrayDist::KL(vector<double const *> const &par1,
			 vector<double const *> const &par2,
			 vector<vector<unsigned long> > const &dims) const
    {
	return JAGS_NA;
    }
    

} //namespace jags
