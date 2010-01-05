#include <config.h>

#include "HolmesHeldFactory.h"
#include "HolmesHeld.h"

using std::vector;

namespace glm {

    HolmesHeldFactory::HolmesHeldFactory()
	: BinaryFactory("Holmes-Held", false)
    {}

    BinaryGLM *
    HolmesHeldFactory::newBinary(GraphView const *view,
				 vector<GraphView const *> const &sub_views,
				 unsigned int chain) const
    {
	return new HolmesHeld(view, sub_views, chain);
    }

}
