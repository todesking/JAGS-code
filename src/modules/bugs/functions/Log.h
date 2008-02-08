#ifndef FUNC_LOG_H_
#define FUNC_LOG_H_

#include <function/ScalarFunc.h>

namespace bugs {

    /**
     * @short Log function
     * @see Exp
     * <pre>
     * y <- log(x)
     * y = log(x) for x > 0
     * </pre>
     */
    class Log : public ScalarFunc
    {
    public:
	Log ();
	double evaluateScalar(std::vector<double const *> const &args) const;
	bool checkScalarValue(std::vector<double const *> const &args) const;
    };

}

#endif /* FUNC_LOG_H_ */