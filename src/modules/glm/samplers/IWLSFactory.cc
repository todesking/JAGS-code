#include <config.h>

#include <graph/StochasticNode.h>

#include "IWLSFactory.h"
#include "IWLS.h"

using std::vector;

namespace glm {

    IWLSFactory::IWLSFactory()
	: GLMFactory("IWLS")
    {}

    bool IWLSFactory::checkOutcome(StochasticNode const *snode,
				   LinkNode const *lnode) const
    {
	switch (GLMMethod::getFamily(snode)) {
	case GLM_NORMAL:
	    return lnode == 0;
	case GLM_UNKNOWN:
	    return false;
	default:
	    return lnode != 0;
	}
    }
    
    GLMMethod *
    IWLSFactory::newMethod(Updater const *updater,
			     vector<Updater const *> const &sub_updaters,
			     unsigned int chain) const
    {
	return new IWLS(updater, sub_updaters, chain);
    }
    
    bool IWLSFactory::canSample(StochasticNode const *snode) const
    {
	vector<Node const *> const &parents = snode->parents();
	for (unsigned int i = 0; i < parents.size(); ++i) {
	    if (!snode->isObserved())
		return false;
	}
	return !isBounded(snode);
    }
}