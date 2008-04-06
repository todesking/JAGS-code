#ifndef FUNC_ADD_H_
#define FUNC_ADD_H_

#include "Infix.h"

namespace basefunctions {

/**
 * The Add function implements the infix operator "+" in the BUGS language.
 * The expression a + b + c is broken down into ((a + b) + c), so two
 * separate calls to Add are made.
 * @short Sum of two scalars
 * <pre>
 * y <- a + b
 * </pre>
 */
class Add : public Infix
{
public:
    Add ();
    double evaluateScalar(std::vector<double const *>const &args) const;
    bool isDiscreteValued(std::vector<bool> const &flags) const;
    bool isLinear(std::vector<bool> const &mask,
		  std::vector<bool> const &fixmask) const;
};

}

#endif /* FUNC_ADD_H_ */